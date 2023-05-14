import math

# define the length of the different parts of the leg

CH = 153.545
CD = 47.273
DH = 107.191
HE = 20
DA = 130
OA = 46.5
omega = math.acos((DH ** 2 + CD ** 2 - CH ** 2) /
                  (2 * CD * DH)) * math.degrees(1)

print(omega)


def get_coordonate_E_simplified(ha, ka):
    AG = 0.0
    EG = 0.0
    beta = (90 - ha)
    teta = ha + ka
    # valid for both configuration of the leg
    gamma = (90 + teta - omega)

    alpha = (gamma + 90)

    AH = math.sqrt(pow(DH, 2) + pow(DA, 2) - (2 * DA *
                   DH * math.cos(alpha * math.pi / 180)))
    little_phi = math.acos(((- pow(DH, 2) + pow(DA, 2) + pow(AH, 2)) /
                           (2 * DA * AH))) * 180 / math.pi

    EG = -(math.sin((beta - little_phi)*math.radians(1))) * AH
    AG = (math.cos((beta - little_phi)*math.radians(1))) * AH + HE
    # Adding radious of the squash ball

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
    AE = math.sqrt(DH ** 2 + DA ** 2 - 2 * DA * DH * math.cos(alpha))
    little_phi = math.acos((-DH ** 2 + DA ** 2 + AE ** 2) /
                           (2 * DA * AE)) * math.degrees(1)

    EG = math.sin(beta - little_phi) * AE
    AG = math.cos(beta - little_phi) * AE

    x = OA * math.cos(sa)
    y = EG
    z = OA * math.sin(sa) + AG

    return x, y, z


def get_angle_simplified(AG, EG):

    false_AG = AG-HE

    HA = math.sqrt(pow(false_AG, 2) + pow(EG, 2))

    epsilon = math.acos(false_AG / HA) * math.degrees(1)

    little_phi = math.acos(
        (-pow(DH, 2) + pow(DA, 2) + pow(HA, 2)) / (2 * DA * HA)) * math.degrees(1)

    # Here we have to think about how to implement the case where the leg is in front

    # hanche = (90 - little_phi - epsilon)

    hanche = (90 - little_phi + epsilon)

    alpha = math.acos((pow(DH, 2) + pow(DA, 2) - pow(HA, 2)
                       ) / (2 * DA * HA)) * math.degrees(1)

    if (HA >= 181.42434761668073):
        ka = (omega + alpha - 180 - hanche)
    else:
        ka = (omega - alpha - hanche)
    coord = [hanche, ka]
    return coord


print(get_coordonate_E_simplified(68.667, 15.43))
print(get_angle_simplified(181.974229501661, 3.2701842427722743))
