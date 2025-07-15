
#include "RedlichKwongGas.H"
#include "mathematicalConstants.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
inline Foam::RedlichKwongGas<Specie>::RedlichKwongGas
        (
                const Specie &sp
        )
        :
        Specie(sp) {

    this->requireRealGasEOS(false);

    static_assert(Foam::is_cubic_EOS<Foam::RedlichKwongGas<Specie>>::value, "RK must be cubic EOS");
}


template<class Specie>
inline Foam::RedlichKwongGas<Specie>::RedlichKwongGas
        (
                const word &name,
                const RedlichKwongGas &pg
        )
        :
        Specie(name, pg) {
    this->requireRealGasEOS(false);
}


template<class Specie>
inline Foam::autoPtr<Foam::RedlichKwongGas<Specie>>
Foam::RedlichKwongGas<Specie>::clone() const {
    return autoPtr<RedlichKwongGas<Specie>>
            (
                    new RedlichKwongGas<Specie>(*this)
            );
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //



// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Specie>
inline void Foam::RedlichKwongGas<Specie>::operator+=
        (
                const RedlichKwongGas<Specie> &pg
        ) {
    notImplemented(__PRETTY_FUNCTION__);
//    scalar X1 = this->Y() / this->W();
//    Specie::operator+=(pg);
//
//    if (mag(this->Y()) > small) {
//        X1 *= this->W() / this->Y();
//        const scalar X2 = this->W() * pg.Y() / (pg.W() * this->Y());
//
//        Tc_ = X1 * Tc_ + X2 * pg.Tc_;
//        Vc_ = X1 * Vc_ + X2 * pg.Vc_;
////        Zc_ = X1 * Zc_ + X2 * pg.Zc_;
//        Pc_ = RR * Zc_ * Tc_ / Vc_;
////        omega_ = X1*omega_ + X2*pg.omega_;
//    }
}


template<class Specie>
inline void Foam::RedlichKwongGas<Specie>::operator*=(const scalar s) {
    notImplemented(__PRETTY_FUNCTION__);
    Specie::operator*=(s);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


template<class Specie>
Foam::RedlichKwongGas<Specie> Foam::operator+
        (
                const RedlichKwongGas<Specie> &pg1,
                const RedlichKwongGas<Specie> &pg2
        ) {
    notImplemented(__PRETTY_FUNCTION__);
    Specie sp
            (
                    static_cast<const Specie &>(pg1)
                    + static_cast<const Specie &>(pg2)
            );

    if (mag(sp.Y()) < small) {
        return RedlichKwongGas<Specie>
                (
                        sp
                );
    } else {

        return RedlichKwongGas<Specie>
                (
                        sp
                );
    }
}


template<class Specie>
Foam::RedlichKwongGas<Specie> Foam::operator*
        (
                const scalar s,
                const RedlichKwongGas<Specie> &pg
        ) {
    return RedlichKwongGas<Specie>
            (
                    s * static_cast<const Specie &>(pg)
            );
}


template<class Specie>
Foam::RedlichKwongGas<Specie> Foam::operator==
        (
                const RedlichKwongGas<Specie> &pg1,
                const RedlichKwongGas<Specie> &pg2
        ) {
    notImplemented(__PRETTY_FUNCTION__);
    return RedlichKwongGas<Specie>
            (
                    static_cast<const Specie &>(pg1) == static_cast<const Specie &>(pg2)
            );
}

