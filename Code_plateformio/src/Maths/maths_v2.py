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


def get_coordonate_E_simplified(ha, ka):
    AG = 0.0
    EG = 0.0
    beta = (90 - ha)
    teta = ha + ka

    # valid for both configuration of the leg
    gamma = (90 + teta - omega)

    print(gamma)

    alpha = (gamma + 90)

    AH = math.sqrt(pow(DH, 2) + pow(DA, 2) - (2 * DA *
                   DH * math.cos(alpha * math.pi / 180)))

    little_phi = math.acos(((- pow(DH, 2) + pow(DA, 2) + pow(AH, 2)) /
                           (2 * DA * AH))) * 180 / math.pi

    EG = (math.sin((abs(beta - little_phi))*math.radians(1))) * AH
    AG = (math.cos((abs(beta - little_phi))*math.radians(1))) * AH + HE

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

    # if EG<=0 à implémenter dans le cpp :
    # hanche = (90 - little_phi - epsilon)
    # else :
    hanche = (90 - little_phi + epsilon)

    alpha = math.acos((pow(DH, 2) + pow(DA, 2) - pow(HA, 2)
                       ) / (2 * DA * DH)) * math.degrees(1)

    if (True or alpha >= 90):
        ka = (omega + alpha - 180 - hanche)
    else:
        ka = (omega + alpha - 180 - hanche)
    coord = [hanche, ka]
    return coord


# Patte bien vers l'arrière
# print(get_coordonate_E_simplified(11.033345999999995, 14.763960999999995))
# print(get_angle_simplified(95.75914841407432, 33.25108890667333))

# Patte bien vers l'avant
# print(get_coordonate_E_simplified(99.998629, 9.005600))
# print(get_angle_simplified(189.182477102606, 121.54603316527479))


# Calibration of the leg to get the correct distance
# print(get_coordonate_E_simplified(68, 8))
# print(get_angle_simplified(179.9474701877878, 50.983042177042776))

print(get_coordonate_E_simplified(88, 8))
print(get_angle_simplified(179.9474701877878, 50.983042177042776))
