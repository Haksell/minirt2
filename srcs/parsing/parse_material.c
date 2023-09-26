#include "minirt.h"

static bool	parse_lambertian(char *attributes, t_material *material)
{
	(void)attributes;
	(void)material;
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

bool	parse_material(char *material_name, char *attributes,
	t_material *material)
{
	if (ft_strcmp(material_name, "lambertian") == 0)
	{
		material->type = MATERIAL_LAMBERTIAN;
		return (parse_lambertian(attributes, material));
	}
	else if (ft_strcmp(material_name, "metal") == 0)
	{
		material->type = MATERIAL_METAL;
		return (parse_metal(attributes, material));
	}
	else if (ft_strcmp(material_name, "dielectric") == 0)
	{
		material->type = MATERIAL_DIELECTRIC;
		return (parse_dielectric(attributes, material));
	}
	return (false);
}