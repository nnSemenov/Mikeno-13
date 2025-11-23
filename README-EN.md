# About
Mikeno is a fork of OpenFOAM, it's Frankensteined for chemical engineering usage.

[简体中文](README.md) [English]

## Goal of this fork
1. Better support for modeling chemical engineering process. 
2. Continually merge upstream updates
3. Build system migration: Replace wmake with CMake.
4. Fix unexpected SIGFPE trapping, mainly for double-precision. (Compiler optimizes float-point computation with SIMD, but they generates unexpected NAN sometimes. These NAN are never used, but emits SIGFPE)

## Modifications

### Utilities
1. `autoCompress`: Compress all heavy fields (non-uniform, including mesh) to gzip, regardless of format(ascii or binary)

### Code and compiler
1. Migrated all subprojects from wmake to modern cmake.
   - Compatible to modern IDEs, high-quality linting from clangd
   - More convenient to import external dependencies
   - More efficient parallel build
   - More convenient for secondary development with `find_package(OpenFOAM CONFIG)`
2. Performance optimization
   - Add `-march=native` for optimization mode, enabling more vectorization from compiler
3. Support `AOCC`.
4. Add `Tc_` `Pc_` `Vc_` `omega_` to `specie` and remove revelant member from `PengRobinsonGas`. In `physicalProperties`, user should write them into `specie` dictionary.
   - Critial point and acentric factor are intrinstic nature similar to mole weight.
   - Makes it more convenient to add more real fluid EOS.

### Support arbitrarily high pressure
1. The `pOffset` keyword can be added to `physicalProperites`, allowing gauge pressure for p-V coupling, and absolute pressure for thermophysical. **Small pressure difference will never be flooded by floating point rounding error(espicially single precision)**.

### Porous media heat transfer
1. `porousMediaFluidSolver` supporting arbitrary number of porous phases, heat transfer between fluid-porous and porous-porous, both supporting thermal equilibrium and non-equilibrium.

### More rigours thermodynamics
1. Equation of state: add `RedlichKwongGas`, rewrite `PengRobinsonGas`
2. Both real gas EOSs are tested with AspenPlusV14
3. Van der vaals mixing rule.
   - Support binary interaction coefficient `k_ij` for `PengRobinsonGas`
4. All thermo models (eq `hConst`) supports `ideal_*` methods that gives ideal gas properties.
5. New mixture model `realGasMulticomponentMixture` 
   1. Compute `rho` from mixed real gas EOS
   2. Compute and add residual properties of `Cp` `Cv` `hs` `ha` `es` `ea`. All residual properties are computed from mixed EOS

## Fix unexpected SIGFPE trapping (compile option in brackes)
1. Fix `flowRateInletVelocity` trapped by SIGFPE when writting flow field. This is caused by division in `unitConversion::toUser(const T& t) const`. (`Clang DP Opt`)


## Pending works
1. More equation of state: Patel-Teja, Martin-Hou
2. Extend porous media heat trSolveransfer to multicomponent
3. Stabilize `porousMediaFluid` for non-equilibrium heat transfer with large coefficient or specific area
4. Modify dynamicCode implementation, use cmake instead of wmake.


## Existing Bugs(Up to 20251123):
1. `decomposePar` crashes with Largrangian fields(Some cases in `test/Largrangian` fail)
2. Some postprocessing fails (`test/postProcessing/channel`)
3. ~~`blockMesh` trapped by SIGFPE when compiled with single-precision, optimization.~~ (Almost impossible to fix, compiler generates SSE instructions that produce NAN but don't use them. Only way is to `unset FOAM_SIGFPE`)
