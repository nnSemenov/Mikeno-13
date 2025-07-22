inline scalar ideal_Cp
(
    const scalar p,
    const scalar T
) const
{
    return ideal_Cv(p, T) - this->R();
}

inline scalar Cp
(
    const scalar p,
    const scalar T
) const
{
    return Cv(p, T) + EquationOfState::CpMCv(p, T);
}


inline scalar ideal_hs
(
    const scalar p,
    const scalar T
) const
{
    return ideal_es(p, T) + p/EquationOfState::rho(p, T);
}

inline scalar hs
(
    const scalar p,
    const scalar T
) const
{
    return es(p, T) + p/EquationOfState::rho(p, T);
}


inline scalar ideal_ha
(
    const scalar p,
    const scalar T
) const
{
    return ideal_ea(p, T) + p/EquationOfState::rho(p, T);
}

inline scalar ha
(
    const scalar p,
    const scalar T
) const
{
    return ea(p, T) + p/EquationOfState::rho(p, T);
}
