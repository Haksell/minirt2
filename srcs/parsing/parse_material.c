#include "minirt.h"

static bool	parse_lambertian(char *attributes, t_material *material)
{
	char	*ka;
	char	*kd;
	char	*ks;
	char	*specular_exponent;

	material->type = MATERIAL_LAMBERTIAN;
	ka = attributes;
	return (get_commas4(ka, &kd, &ks, &specular_exponent)
		&& ft_atof_range(ka, &material->u.lambertian.ka, 0, 1)
		&& ft_atof_range(kd, &material->u.lambertian.kd, 0, 1)
		&& ft_atof_range(ks, &material->u.lambertian.ks, 0, 1)
		&& ft_atof_range(specular_exponent,
			&material->u.lambertian.specular_exponent, 0, INFINITY));
}

static bool	parse_metal(char *attributes, t_material *material)
{
	material->type = MATERIAL_METAL;
	return (ft_atof_range(attributes, &material->u.metal.fuzz, 0, INFINITY));
}

static bool	parse_dielectric(char *attributes, t_material *material)
{
	material->type = MATERIAL_DIELECTRIC;
	return (ft_atof_range(attributes, &material->u.dielectric.ir, 0, INFINITY)
		&& material->u.dielectric.ir > 0);
}

bool	parse_material(char *material_name, char *attributes,
	t_material *material)
{
	if (ft_strcmp(material_name, "lambertian") == 0)
		return (parse_lambertian(attributes, material));
	else if (ft_strcmp(material_name, "metal") == 0)
		return (parse_metal(attributes, material));
	else if (ft_strcmp(material_name, "dielectric") == 0)
		return (parse_dielectric(attributes, material));
	return (false);
}