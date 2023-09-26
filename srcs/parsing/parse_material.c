#include "minirt.h"

static bool	parse_lambertian(char *attributes, t_material *material)
{
	material->type = MATERIAL_LAMBERTIAN;
	material->u.lambertian.ka = 0.5;
	material->u.lambertian.kd = 0.8;
	material->u.lambertian.ks = 0.2;
	material->u.lambertian.specular_exponent = 5;
	(void)attributes;
	return (true);
}

static bool	parse_metal(char *attributes, t_material *material)
{
	(void)attributes;
	(void)material;
	return (true);
}

static bool	parse_dielectric(char *attributes, t_material *material)
{
	(void)attributes;
	(void)material;
	return (true);
}

bool	parse_material(char *material_name, char *attributes, t_vec3 color,
	t_material *material)
{
	if (ft_strcmp(material_name, "lambertian") == 0)
	{
		material->type = MATERIAL_LAMBERTIAN;
		material->albedo = color / 255;
		return (parse_lambertian(attributes, material));
	}
	else if (ft_strcmp(material_name, "metal") == 0)
	{
		material->type = MATERIAL_METAL;
		material->albedo = color / 255;
		return (parse_metal(attributes, material));
	}
	else if (ft_strcmp(material_name, "dielectric") == 0)
	{
		material->type = MATERIAL_DIELECTRIC;
		material->albedo = color / 255;
		return (parse_dielectric(attributes, material));
	}
	return (false);
}