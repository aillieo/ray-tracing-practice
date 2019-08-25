#pragma once

#include "Ray.h"
#include "Vector3.h"
#include "Color.h"
#include "Hitable.h"
#include "Random.h"

namespace raytracing_1
{
    class Material
    {
    public:
        // scattered Ray: reflection or refraction
        virtual bool scatter(const Ray& rayIn, const RaycastHit& hitInfo, Color& attenuation, Ray& scattered) const = 0;
    };


    // lambertian 散射材质
    // 漫反射： 随机的方向反射
    // 吸收衰减： albedo->attenuation
    class MatLambertian : public Material
    {
    public:
        MatLambertian() : albedo(Color::White) {}
        MatLambertian(const Color& c) : albedo(c) {}
        virtual bool scatter(const Ray& rayIn, const RaycastHit& hitInfo, Color& attenuation, Ray& scattered) const
        {
            // 随机反射 使用相切的单位球来获取随机点
            Vector3 target = hitInfo.hitPoint + hitInfo.normal + Random::randomInUnitSphere();
            scattered = Ray(hitInfo.hitPoint, target - hitInfo.hitPoint);
            attenuation = albedo;
            return true;
        }
    private:
        Color albedo;
    };

    // metal 金属材质
    // 相比于lambertian 金属的反射是严格按照反射角度 
    // 有很小的一个随机 在反射光线的终点RandomInUnitSphere 用fuzz控制
    class MatMetal : public Material
    {
    public:
        MatMetal() : albedo(Color::White), fuzz(1) {};
        MatMetal(const Color& c, const float f) : albedo(c) 
        {
            fuzz = MathUtils::min<float>(1, f);
        }
        virtual bool scatter(const Ray& rayIn, const RaycastHit& hitInfo, Color& attenuation, Ray& scattered) const 
        {
            Vector3 reflected = reflect(normalize(rayIn.direction), hitInfo.normal);
            scattered = Ray(hitInfo.hitPoint, reflected + fuzz * Random::randomInUnitSphere());
            attenuation = albedo;
            // 由于有fuzz存在 会出现scattered和normal点积小于<=0 这种情况返回false 
            return (dot(scattered.direction, hitInfo.normal) > 0);
        }
    private:
        Color albedo;
        float fuzz;
    };

    // dielectric 电介质材质
    // 有反射也有折射
    // 无损耗 attenuation = 1,1,1
    // ref_idx 折射系数 air = 1, glass = 1.3-1.7, diamond = 2.4
    // 外部介质是空气 因此ni_over_nt（折射系数：入射/折射）取 ref_idx 或 1/ref_idx
    // 计算 reflect_prob 系数 反射比重
    class MatDielectric : public Material
    {
    public:
        MatDielectric() : ref_idx(1.5) {}
        MatDielectric(float ri) : ref_idx(ri) {}
        virtual bool scatter(const Ray& rayIn, const RaycastHit& hitInfo, Color& attenuation, Ray& scattered) const  {
            
            Vector3 outward_normal;
            
            Vector3 reflected = reflect(rayIn.direction, hitInfo.normal);
            float ni_over_nt;
            attenuation = Color(1.0, 1.0, 1.0);
            Vector3 refracted;
            float reflect_prob;
            float cosine;
            if (dot(rayIn.direction, hitInfo.normal) > 0) {
                // 由外部射入
                outward_normal = -hitInfo.normal;
                ni_over_nt = ref_idx;
                cosine = dot(rayIn.direction, hitInfo.normal) / rayIn.direction.length();
                // 此时 cosine表示折射光线的 cos
                // 根据 入射角度 折射系数（入射/折射） 计算折射角度 余弦
                cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
            }
            else {
                // 由内部射出
                outward_normal = hitInfo.normal;
                ni_over_nt = 1.0 / ref_idx;
                // 此时 cosine表示入射光线的 cos
                cosine = -dot(rayIn.direction, hitInfo.normal) / rayIn.direction.length();
            }
            
            // 使用 schlick 近似 得出
            if (refract(rayIn.direction, outward_normal, ni_over_nt, refracted))
                reflect_prob = schlick(cosine, ref_idx);
            else
                reflect_prob = 1.0;
            if (Random::random01() < reflect_prob)
                // 发生了反射
                scattered = Ray(hitInfo.hitPoint, reflected);
            else
                // 发生了折射
                scattered = Ray(hitInfo.hitPoint, refracted);
            return true;
        }
    private:
        float ref_idx;
    };
}


