# 简介
OpenFOAMCE 是 OpenFOAM 的魔改版（分支），面向化工应用。

[简体中文] [English](./README-EN.md)

## 这个分支的目标
1. 更好的支持化工CFD模拟
2. 删除代码（求解器模块）中的冗余引用。这些冗余的引用阻止二次开发者替换父类成员（引用没法改变，比如`thermo_`引用了`thermoPtr`），限制了二次开发。

## 修改内容

### 支持任意高的压力

1. 向 `physicalProperites` 字典中添加 `pOffset` 字段（可选），允许在压速耦合计算时采用表压，更新物性时用绝对压力。**这样较小的压降不会再被浮点计算误差掩盖（特别是单精度模式）**.

### 多孔介质传热
1. `porousMediaFluid` 模块允许任意数量的多孔相，可以模拟流-固传热和固-固传热，同时支持热平衡模式和热非平衡模式。

### 更严格的热力学
1. 状态方程：增加 `RedlichKwongGas`，重写 `PengRobinsonGas`
2. 以上的真实气体状态方程都用AspenPlusV14检验过
3. Van der vaals 混合规则
   - `PengRobinsonGas` 支持二元交互系数 `k_ij`
4. 所有热力学模型（比如 `hConst`）具有形如 `ideal_*` 的接口，提供理想气体的物性。
5. 新的混合物模型 `realGasMulticomponentMixture` 
   1. 依靠混合气体的混合状态方程计算 `rho`
   2. 从剩余性质计算以下物性的真实性质： `Cp` `Cv` `hs` `ha` `es` `ea`。所有剩余性质都是从混合状态方程计算的。

### 代码与编译器
1. 支持 `AOCC`.
2. 在 `specie` 字典中添加 `Tc_` `Pc_` `Vc_` `omega_` 字段，从 `equationOfState`字典中删除相应字段。在编写 `physicalProperties` 时，用户应该把临界性质和偏心因子写入 `specie` 字典。
   - 理由：临界点和偏心因子是物质的本征性质，与摩尔量类似
   - 这样更方便添加其他真实气体状态方程
3. 删除一些求解器模块代码中的冗余引用
   1. 目前清理了 `isothermalFluid`、`fluid`、`multicomponentFluid`、`XiFluid`。


## 计划添加的
1. 更多状态方程：Patel-Teja、Martin-Hou等
2. 把多孔介质传热模块拓展到单相多组分
3. 改进`porousMediaFluid`的热非平衡模型，使它在大比表面积、高传热系数时更加稳定
4. 删除所有求解器模块中的冗余引用


## 现存bug(截至20250823):
1. 算例包含拉格朗日场时，`decomposePar`崩溃（`test/Largrangian`的一些算例测试不通过）
2. `test/postProcessing/channel`的一些后处理算例不通过
3. ~~单精度+优化时`blockMesh`因SIGFPE崩溃~~（无解，编译器优化产生的SSE指令会除零产生NAN，但不使用错误结果。只能取消SIGFPE）