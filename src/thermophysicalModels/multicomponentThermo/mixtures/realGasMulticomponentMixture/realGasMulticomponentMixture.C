#include "realGasMulticomponentMixture.H"

template<class ThermoType>
template<class Method, class ... Args>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::
massWeighted
        (
                Method psiMethod,
                const Args& ... args
        ) const
{
    scalar psi = 0;

    forAll(Y_, i)
    {
        psi += Y_[i]*(specieThermos_[i].*psiMethod)(args ...);
    }

    return psi;
}


template<class ThermoType>
template<class Method, class ... Args>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::
harmonicMassWeighted
        (
                Method psiMethod,
                const Args& ... args
        ) const
{
    scalar rPsi = 0;

    forAll(Y_, i)
    {
        rPsi += Y_[i]/(specieThermos_[i].*psiMethod)(args ...);
    }

    return 1/rPsi;
}


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::limit
        (
                const scalar T
        ) const
{
    return T;
}


template<class ThermoType>
template<class Method, class ... Args>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::transportMixtureType::
moleWeighted
        (
                Method psiMethod,
                const Args& ... args
        ) const
{
    scalar psi = 0;

    forAll(X_, i)
    {
        psi += X_[i]*(specieThermos_[i].*psiMethod)(args ...);
    }

    return psi;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermoType>
Foam::realGasMulticomponentMixture<ThermoType>::realGasMulticomponentMixture
        (
                const dictionary& dict
        )
        :
        multicomponentMixture<ThermoType>(dict),
        thermoMixture_(this->specieThermos()),
        transportMixture_(this->specieThermos())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::W() const
{
    return harmonicMassWeighted(&ThermoType::W);
}


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::rho
        (
                scalar p,
                scalar T
        ) const
{
    return harmonicMassWeighted(&ThermoType::rho, p, T);
}


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::psi
        (
                scalar p,
                scalar T
        ) const
{
    scalar oneByRho = 0;
    scalar psiByRho2 = 0;

    forAll(Y_, i)
    {
        const scalar rhoi = specieThermos_[i].rho(p, T);
        const scalar psii = specieThermos_[i].psi(p, T);

        oneByRho += Y_[i]/rhoi;

        if (psii > 0)
        {
            psiByRho2 += Y_[i]*psii/sqr(rhoi);
        }
    }

    return psiByRho2/sqr(oneByRho);
}


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::hf() const
{
    return massWeighted(&ThermoType::hf);
}


#define thermoMixtureFunction(Func)                                            \
                                                                               \
    template<class ThermoType>                                                 \
    Foam::scalar                                                               \
    Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::Func      \
    (                                                                          \
        scalar p,                                                              \
        scalar T                                                               \
    ) const                                                                    \
    {                                                                          \
        return massWeighted(&ThermoType::Func, p, T);                          \
    }

thermoMixtureFunction(Cp)
thermoMixtureFunction(Cv)
thermoMixtureFunction(hs)
thermoMixtureFunction(ha)
thermoMixtureFunction(Cpv)
thermoMixtureFunction(gamma)
thermoMixtureFunction(he)


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType::The
        (
                const scalar he,
                scalar p,
                scalar T0
        ) const
{
    return ThermoType::T
            (
                    *this,
                    he,
                    p,
                    T0,
                    &thermoMixtureType::he,
                    &thermoMixtureType::Cpv,
                    &thermoMixtureType::limit
            );
}


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::transportMixtureType::mu
        (
                scalar p,
                scalar T
        ) const
{
    return moleWeighted(&ThermoType::mu, p, T);
}


template<class ThermoType>
Foam::scalar
Foam::realGasMulticomponentMixture<ThermoType>::transportMixtureType::kappa
        (
                scalar p,
                scalar T
        ) const
{
    return moleWeighted(&ThermoType::kappa, p, T);
}


template<class ThermoType>
const typename
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixtureType&
Foam::realGasMulticomponentMixture<ThermoType>::thermoMixture
        (
                const scalarFieldListSlice& Y
        ) const
{
    scalar sumX = 0;
    forAll(Y, i)
    {
        thermoMixture_.Y_[i] = Y[i];
        thermoMixture_.X_[i] = Y[i]/this->specieThermos()[i].W();
        sumX += thermoMixture_.X_[i];
    }

    forAll(Y, i)
    {
        thermoMixture_.X_[i] /= sumX;
    }

    return thermoMixture_;
}


template<class ThermoType>
const typename
Foam::realGasMulticomponentMixture<ThermoType>::transportMixtureType&
Foam::realGasMulticomponentMixture<ThermoType>::transportMixture
        (
                const scalarFieldListSlice& Y
        ) const
{
    scalar sumX = 0;

    forAll(Y, i)
    {
        transportMixture_.X_[i] = Y[i]/this->specieThermos()[i].W();
        sumX += transportMixture_.X_[i];
    }

    forAll(Y, i)
    {
        transportMixture_.X_[i] /= sumX;
    }

    return transportMixture_;
}


template<class ThermoType>
const typename
Foam::realGasMulticomponentMixture<ThermoType>::transportMixtureType&
Foam::realGasMulticomponentMixture<ThermoType>::transportMixture
        (
                const scalarFieldListSlice& Y,
                const thermoMixtureType&
        ) const
{
    return transportMixture(Y);
}
