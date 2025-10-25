lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(ODE SHARED
    ODESolvers/ODESolver/ODESolver.C
    ODESolvers/ODESolver/ODESolverNew.C

    ODESolvers/adaptiveSolver/adaptiveSolver.C
    ODESolvers/Euler/Euler.C
    ODESolvers/EulerSI/EulerSI.C
    ODESolvers/Trapezoid/Trapezoid.C
    ODESolvers/RKF45/RKF45.C
    ODESolvers/RKCK45/RKCK45.C
    ODESolvers/RKDP45/RKDP45.C
    ODESolvers/Rosenbrock12/Rosenbrock12.C
    ODESolvers/Rosenbrock23/Rosenbrock23.C
    ODESolvers/Rosenbrock34/Rosenbrock34.C
    ODESolvers/rodas23/rodas23.C
    ODESolvers/rodas34/rodas34.C
    ODESolvers/SIBS/SIBS.C
    ODESolvers/SIBS/SIMPR.C
    ODESolvers/SIBS/polyExtrapolate.C
    ODESolvers/seulex/seulex.C

    ODESystem/ODESystem.C
)
target_include_directories(ODE PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_link_libraries(ODE PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific
)

install(TARGETS ODE
    DESTINATION lib
)