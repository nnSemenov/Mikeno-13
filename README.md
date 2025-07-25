# About
OpenFOAMCE is a fork of OpenFOAM, it's Frankensteined for chemical engineering usage.

## Goal of this fork
1. Better support for modeling chemical engineering process.
2. Remove redundant reference in modules. These redundant references forbids subclass from changing parent class's member(e.g. `thermo_` references `thermoPtr`), thus limiting liberty of secondary developing.

## Modifications

### Support abritarily high pressure

1. The `pOffset` keyword can be added to `physicalProperites`, allowing gauge pressure for p-V coupling, and absolute pressure for thermophysical. **Small pressure difference will never be flooded by floating point rounding error(espicially single precision)**.


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
1. More equation of state: Patel-Teja, Martin-Hou.
2. Porous media model in the spirit of AnsysFluent.
   1. (OpenFOAM doesn't consider heat transfer in porous media)
3. Remove more redundant reference member in all solver modules.