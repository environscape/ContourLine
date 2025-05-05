# ContourLine Arduino DCO
The Eurorack modular is based on the Arduino-Mozzi library.

## 简介
欢迎使用ContourLine，这是一款开源的Eurorack数字振荡器。该振荡器基于**Arduino Nano控制器**与**Mozzi库**开发，通过简洁的硬件设计与丰富的软件功能，实现多样化的音频合成效果。

用户可通过两个按钮切换旋钮调节功能与参数列表，并借助8位数码管实时显示当前设置。参数修改采用"接近解锁"机制：当旋钮调节至目标参数附近时，数码管亮度提升，即表示该参数已解锁可编辑状态。

项目已提供完整的Gerber文件、BOM清单及物料列表。若需定制PCB板，可参考B站用户ciiyte发布的教程，通过嘉立创等厂商完成制作。

![面板效果图2](Hardware/img/面板效果图2.jpg)

## 模块参数
| 项目         | 参数规格                     |
|--------------|----------------------------|
| 电源接口      | 10针连接器                  |
| +12V功耗      | 约25mA                     |
| -12V功耗      | 约5mA                      |
| Eurorack规格  | 4HP宽度，30mm深度           |
| 操作部件      | 1个旋钮，2个按钮，1个8位数码管 |
| 信号接口      | 1x VOCT输入，3x CV输入，1x Gate输入，1x 音频输出 |

## 硬件设计
1. **核心控制**：采用Arduino Nano控制器，内置8路ADC输入通道，可直接兼容Eurorack标准的0-5V控制信号，无需额外放大电路，大幅简化PCB设计。
2. **交互设计**：通过按钮切换菜单、单旋钮调整参数、数码管显示状态的设计方案，在保持硬件简洁性的同时，具备良好的功能扩展性，支持未来参数与调制功能的升级。
3. **信号处理**：针对不同类型的CV信号（低频控制、音频、VOCT、门控信号等），采用差异化电路设计，确保信号处理的准确性与稳定性。

## 现有程序实现
项目已开发多种音频合成算法，涵盖振荡器、打击乐发生器、采样器等功能模块，具体包括：
- [Avr-wt-synth故障振荡器](Software/Avr-wt-synth/readme.md)
- [虚拟模拟振荡器](Software/AnalogWave/readme.md)
- [可调制打击乐发生器](Software/DrumVoltrixion/readme.md)
- [和弦/加法/FM振荡器](Software/FmAddChordDCO/readme.md)
- [2算子FM振荡器（入门）](Software/FmDCO/readme.md)
- [波型渐变2算子FM振荡器（推荐）](Software/FmWsWtDCO/readme.md)
- [波型渐变2算子FM振荡器（lofi版）](Software/FmWsWtDCOfor168p/readme.md)
- [4组打击乐发生器](Software/FourTrekPerc/readme.md)
- [粒子合成器](Software/Granular/readme.md)
- [和谐音程振荡器](Software/HarmonicOSC/readme.md)
- [风噪音发生器](Software/NoiseWindy/readme.md)
- [4K采样器](Software/Sampler/readme.md)
- [失谐振荡器](Software/Swarmduino/readme.md)

更多程序详见：[软件仓库](https://github.com/lechenghhh/ContourLine/tree/master/Software)

## 程序拓展说明
### 技术原理
本项目基于**Mozzi库**开发。Arduino Nano虽无内置DAC模块，但通过PWM（脉宽调制）结合RC滤波电路，依据奈奎斯特采样定理，在高采样率下实现高质量音频输出。

### 主程序结构（以波型渐变2算子FM振荡器为例）
1. **setup()**：初始化控制引脚、数码管引脚配置，启动Mozzi库运行环境。
2. **updateControl()**：实时获取菜单状态、旋钮参数、按钮输入及CV信号数据，经运算生成音频合成基础参数。
3. **updateAudio()**：执行核心音频合成算法，输出PWM格式音频信号。该函数为实时音频处理模块，严禁包含复杂控制逻辑。
4. **loop()**：调用Mozzi库的`audioHook()`函数，请勿修改此部分代码以确保音频处理的实时性。

如需技术讨论或功能建议，欢迎访问：[项目讨论区](https://github.com/environscape/ContourLine/issues) 
