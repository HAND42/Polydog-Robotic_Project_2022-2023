import math

# define the length of the different parts of the leg

CE = 170.5
CD = 47.273
DE = 124.7
DA = 130
OA = 46.5
omega = math.acos((DE ** 2 + CD ** 2 - CE ** 2) /
                  (2 * CD * DE)) * math.degrees(1)

print(omega)


def get_coordonate_E_simplified(ha, ka):
    AG = 0.0
    EG = 0.0
    beta = (90 - ha)
    teta = ha + ka
    # valid for both configuration of the leg
    gamma = (90 + teta - omega)

    alpha = (gamma + 90)

    AE = math.sqrt(pow(DE, 2) + pow(DA, 2) - (2 * DA *
                   DE * math.cos(alpha * math.radians(1))))
    little_phi = math.acos(((- pow(DE, 2) + pow(DA, 2) + pow(AE, 2)) /
                           (2 * DA * AE)))*math.degrees(1)

    EG = (math.sin((beta - little_phi)*math.radians(1))) * AE
    AG = (math.cos((beta - little_phi)*math.radians(1))) * AE

    return AG, EG


def get_coordonate_E(ha, ka, sa):
    x, y, z = 0.0, 0.0, 0.0

    AG = 0.0
    EG = 0.0
    beta = (math.pi / 2 - ha) * math.degrees(1)
    teta = (ha + ka) * math.degrees(1)
    # valid for both configuration of the leg
    gamma = (math.pi / 2 + teta - omega) * math.degrees(1)
    alpha = (gamma + math.pi / 2) * math.degrees(1)
    AE = math.sqrt(DE ** 2 + DA ** 2 - 2 * DA * DE * math.cos(alpha))
    little_phi = math.acos((-DE ** 2 + DA ** 2 + AE ** 2) /
                           (2 * DA * AE)) * math.degrees(1)

    EG = math.sin(beta - little_phi) * AE
    AG = math.cos(beta - little_phi) * AE

    x = OA * math.cos(sa)
    y = EG
    z = OA * math.sin(sa) + AG

    return x, y, z


def get_angle_simplified(AG, EG):
    EA = math.sqrt(pow(AG, 2) + pow(EG, 2))

    epsilon = math.acos(AG / EA) * math.degrees(1)

    little_phi = math.acos(
        (-pow(DE, 2) + pow(DA, 2) + pow(EA, 2)) / (2 * DA * EA)) * math.degrees(1)
    ha = (90 - little_phi - epsilon)

    alpha = math.acos((pow(DE, 2) + pow(DA, 2) - pow(EA, 2)
                       ) / (2 * DA * DE)) * math.degrees(1)

    if (EA >= 181.42434761668073):
        ka = (omega + alpha - 180 - ha)
    else:
        ka = (omega - alpha - ha)

    coord = [ha, ka]
    return coord


print(get_coordonate_E_simplified(45.734656934193225, 28.63743040958647))
print(get_angle_simplified(181.974229501661, 3.2701842427722743))
