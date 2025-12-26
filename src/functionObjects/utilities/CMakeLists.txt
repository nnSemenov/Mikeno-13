lnInclude(${CMAKE_CURRENT_SOURCE_DIR})

set(target_name utilityFunctionObjects)

add_library(${target_name} SHARED
    codedFunctionObject/codedFunctionObject.C
    residuals/residuals.C
    timeActivatedFileUpdate/timeActivatedFileUpdate.C
    timeStep/timeStepFunctionObject.C
    userTimeStep/userTimeStepFunctionObject.C
    setTimeStep/setTimeStepFunctionObject.C
    setWriteInterval/setWriteIntervalFunctionObject.C
    systemCall/systemCall.C
    stopAt/stopAt.C
    stopAt/stopAtFile/stopAtFile.C
    stopAt/stopAtClockTime/stopAtClockTime.C
    stopAt/stopAtTimeStep/stopAtTimeStep.C
    removeObjects/removeObjects.C
    writeDictionary/writeDictionary.C
    writeObjects/writeObjects.C
    writeMesh/writeMesh.C
    time/timeFunctionObject.C
    checkMesh/checkMesh.C
)

target_include_directories(${target_name} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/lnInclude"
)

target_include_directories(${target_name} PRIVATE

)

target_link_libraries(${target_name} PRIVATE
    OpenFOAM_Defines
    OpenFOAM
    OSspecific

    finiteVolume
    meshCheck
    sampling
)

target_compile_definitions(${target_name} PRIVATE
    LIB_NAME=lib${target_name}.so
)

set(FOAM_regular_libraries "${FOAM_regular_libraries};${target_name}" PARENT_SCOPE)


