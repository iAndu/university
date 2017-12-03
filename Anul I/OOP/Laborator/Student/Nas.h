#ifndef NAS_H_INCLUDED
#define NAS_H_INCLUDED

enum E_TIP_NAS {
    E_TIP_NAS_CARN = 48,
    E_TIP_NAS_DREPT = 67,
    E_TIP_NAS_PERFECT
};

class Nas {
public:
    E_TIP_NAS m_tipNas;
    Nas() : m_tipNas(E_TIP_NAS_PERFECT) { };
};

#endif // NAS_H_INCLUDED
