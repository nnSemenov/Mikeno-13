lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

add_library(chemistryModel SHARED
    basicChemistryModel/basicChemistryModel.C
    basicChemistryModel/basicChemistryModelNew.C

    chemistrySolver/chemistrySolver/chemistrySolvers.C
    chemistrySolver/noChemistrySolver/noChemistrySolvers.C
    chemistrySolver/EulerImplicit/EulerImplicitChemistrySolvers.C
    chemistrySolver/ode/odeChemistrySolvers.C

    odeChemistryModel/odeChemistryModel.C

    chemistryModel/reduction/chemistryReductionMethod/chemistryReductionMethods.C
    chemistryModel/reduction/noChemistryReduction/noChemistryReductionMethods.C
    chemistryModel/reduction/DAC/DACChemistryReductionMethods.C
    chemistryModel/reduction/DRG/DRGChemistryReductionMethods.C
    chemistryModel/reduction/DRGEP/DRGEPChemistryReductionMethods.C
    chemistryModel/reduction/EFA/EFAChemistryReductionMethods.C
    chemistryModel/reduction/PFA/PFAChemistryReductionMethods.C

    chemistryModel/tabulation/chemistryTabulationMethod/chemistryTabulationMethod.C
    chemistryModel/tabulation/chemistryTabulationMethod/chemistryTabulationMethodNew.C
    chemistryModel/tabulation/noChemistryTabulation/noChemistryTabulation.C
    chemistryModel/tabulation/ISAT/ISAT.C
    chemistryModel/tabulation/ISAT/chemPointISAT/chemPointISAT.C
    chemistryModel/tabulation/ISAT/binaryNode/binaryNode.C
    chemistryModel/tabulation/ISAT/binaryTree/binaryTree.C

    reaction/makeReactions.C

    functionObjects/adjustTimeStepToChemistry/adjustTimeStepToChemistry.C
    functionObjects/reactionRates/reactionRates.C
    functionObjects/specieReactionRates/specieReactionRates.C
)

target_include_directories(chemistryModel PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(chemistryModel PRIVATE
    ${LIB_SRC}/physicalProperties/lnInclude
    ${LIB_SRC}/thermophysicalModels/specie/lnInclude
    ${LIB_SRC}/thermophysicalModels/functions/Polynomial
)

target_link_libraries(chemistryModel PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    fluidThermophysicalModels 
    multicomponentThermophysicalModels 
    specie 
    ODE 
    finiteVolume 
    meshTools
)

install(TARGETS chemistryModel
    DESTINATION lib
)