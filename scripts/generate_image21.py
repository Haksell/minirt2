from random import random, randint, uniform

lines = """\
A	1.0	220,235,255
C	13,2,3	-0.9636241116594315,-0.14824986333222023,-0.22237479499833035	37

sp	0,-1000,0	2000	128,128,128 lambertian 0.5,0.8,0.2,5
sp	-4,1,0	2	104,52,26 lambertian 0.5,0.8,0.2,5
sp	0,1,0	2	255,255,255 dielectric 1.5
sp	4,1,0	2	182,156,130 metal 0.0""".split(
    "\n"
)

for a in range(-10, 11):
    for b in range(-10, 11):
        mat = random()
        while True:
            x = a + uniform(0, 0.9)
            y = 0.2
            z = b + uniform(0, 0.9)
            dy = (y - 0.2) ** 2
            dz = z**2
            if all((x - sx) ** 2 + dy + dz > 0.9 for sx in (-4, 0, 4)):
                break
        r, g, b = randint(0, 255), randint(0, 255), randint(0, 255)
        if mat < 0.65:
            material = "lambertian"
            ka = uniform(0.5, 1)
            kd = uniform(0.5, 1)
            ks = 1 - kd
            specular_exponent = randint(1, 15)
            lines.append(
                f"sp\t{x:.3f},{y:.3f},{z:.3f}\t0.4\t{r},{g},{b}\t{material}\t{ka:.2f},{kd:.2f},{ks:.2f},{specular_exponent}"
            )
        elif mat < 0.85:
            material = "metal"
            fuzz = uniform(0, 0.5)
            lines.append(
                f"sp\t{x:.3f},{y:.3f},{z:.3f}\t0.4\t{r},{g},{b}\t{material}\t{fuzz:.2f}"
            )
        else:
            material = "dielectric"
            ir = 1.5
            lines.append(
                f"sp\t{x:.3f},{y:.3f},{z:.3f}\t0.4\t{r},{g},{b}\t{material}\t{ir}"
            )

open("scenes/bonus/image21.rtb", "w").write("\n".join(lines))
