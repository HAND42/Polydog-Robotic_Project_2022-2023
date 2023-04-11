import math

# define the length of the different parts of the leg

CE = 170.5
CD = 47.273
DE = 124.7
DA = 130
OA = 46.5
omega = math.acos((DE ** 2 + CD ** 2 - CE ** 2) / (2 * CD * DE))


def get_coordonate_E_simplified(ha, ka):
    AG = 0.0
    EG = 0.0
    beta = math.pi / 2 - ha
    teta = ha + ka
    # valid for both configuration of the leg
    gamma = (math.pi / 2 + teta - omega) * math.degrees(1)
    alpha = gamma + math.pi / 2
    AE = math.sqrt(DE ** 2 + DA ** 2 - 2 * DA * DE * math.cos(alpha))
    little_phi = math.acos((-DE ** 2 + DA ** 2 + AE ** 2) / (2 * DA * AE))

    EG = math.sin(beta - little_phi) * AE
    AG = math.cos(beta - little_phi) * AE

    return AG, EG


def get_coordonate_E(ha, ka, sa):
    x, y, z = 0.0, 0.0, 0.0

    AG = 0.0
    EG = 0.0
    beta = math.pi / 2 - ha
    teta = ha + ka
    # valid for both configuration of the leg
    gamma = (math.pi / 2 + teta - omega) * math.degrees(1)
    alpha = gamma + math.pi / 2
    AE = math.sqrt(DE ** 2 + DA ** 2 - 2 * DA * DE * math.cos(alpha))
    little_phi = math.acos((-DE ** 2 + DA ** 2 + AE ** 2) / (2 * DA * AE))

    EG = math.sin(beta - little_phi) * AE
    AG = math.cos(beta - little_phi) * AE

    x = OA * math.cos(sa)
    y = EG
    z = OA * math.sin(sa) + AG

    return x, y, z
