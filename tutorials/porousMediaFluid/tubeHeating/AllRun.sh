#! /bin/bash
foamListTimes -rm

setFields

foamRun

foamPostProcess -latestTime -func "patchAverage(T,patch=outlet)"