# About
OpenFOAMCE is a fork of OpenFOAM, it's Frankensteined for chemical engineering usage.

[简体中文](README.md) [English]

## Goal of this fork
1. Better support for modeling chemical engineering process.
2. Remove redundant reference in modules. These redundant references forbids subclass from changing parent class's member(e.g. `thermo_` references `thermoPtr`), thus limiting liberty of secondary developing.

## Modifications

### Support abritarily high pressure

1. The `pOffset` keyword can be added to `physicalProperites`, allowing gauge pressure for p-V coupling, and absolute pressure for thermophysical. **Small pressure difference will never be flooded by floating point rounding error(espicially single precision)**.

### Porous media heat transfer
1. `porousMediaFluid` supporting arbitary number of porous phases, heat transfer between fluid-porous and porous-porous, both supporting thermal equilibrium and non-equilibrium.

### More rigous thermodynamics
1. Equation of state: add `RedlichKwongGas`, rewrite `PengRobinsonGas`
2. Both real gas EOSs are tested with AspenPlusV14
3. Van der vaals mixing rule.
   - Support binary interaction coefficient `k_ij` for `PengRobinsonGas`
4. All thermo models (eq `hConst`) supports `ideal_*` methods that gives ideal gas properties.
5. New mixture model `realGasMulticomponentMixture` 
   1. Compute `rho` from mixed real gas EOS
   2. Compute and add residual properties of `Cp` `Cv` `hs` `ha` `es` `ea`. All residual properties are computed from mixed EOS
### Code and compiler
1. Support `AOCC`.
2. Add `Tc_` `Pc_` `Vc_` `omega_` to `specie` and remove revelant member from `PengRobinsonGas`. In `physicalProperties`, user should write them into `specie` dictionary.
   - Critial point and acentric factor are intrinstic nature similar to mole weight.
   - Makes it more convenient to add more real fluid EOS.
3. Remove some redundant reference in solver module
   1. Currently cleaned `isothermalFluid`, `fluid`, `multicomponentFluid`, `XiFluid`.


## Pending works
1. More equation of state: Patel-Teja, Martin-Hou
2. Extend porous media heat transfer to multicomponent
3. Stabilize `porousMediaFluid` for non-equilibrium heat transfer with large coefficient or specific area
4. Remove more redundant reference member in all solver modules


## Existing Bugs(Up to 20250823):
1. `decomposePar` crashes with Largrangian fields(Some cases in `test/Largrangian` fail)
2. Some postprocessing fails (`test/postProcessing/channel`)
3. ~~`blockMesh` trapped by SIGFPE when compiled with single-precision, optimization.~~ (Almost impossible to fix, compiler generates SSE instructions that produce NAN but don't use them. Only way is to `unset FOAM_SIGFPE`)