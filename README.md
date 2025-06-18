# wemap

> 一个轻量的纯 C 命令行工具，用于快速生成 Skyrim MOD 《龙裔话外音》所需的中英文对照 JSON 映射文件。

---

## 🔍 工具介绍

`wemap` 是一个为《上古卷轴5：天际》MOD 制作者量身打造的小工具，支持从 `.esm/.esp` 和 `.strings` 文件中提取对话内容，并将中英文本对应输出为 JSON 文件，适配 MOD 项目《龙裔话外音》的语音文本需求。

工具名称由以下单词组合而来：

- **w**alk – 遍历 ESM 文件结构  
- **e** – 代表 `read` 与 `get` 的共有核心字母  
- **m**ap – 映射文本  

---

## ⚙️ 使用方法

打开命令行，进入 `wemap` 可执行文件所在目录，输入如下命令：

```bash
.\wemap.exe -E英文插件.esp -C中文插件.esp [-SE英文.strings] [-SC中文.strings] > output.json

参数说明：

参数    说明

-E    英文原版 .esm/.esp 文件
-C    中文翻译版 .esm/.esp 文件
-SE    英文 .strings 文件（可选）
-SC    中文 .strings 文件（可选）
>    输出重定向，写入目标 JSON 文件


参数顺序无要求，但 -E 和 -C 至少需要提供一个。


---

🧪 示例

示例 1：非本地化插件（如 3DNPC）

.\wemap.exe -E3DNPC_en.esp -C3DNPC_cn.esp > 3DNPC.json

示例 2：使用 strings 的插件（如 Skyrim.esm）

.\wemap.exe -ESkyrim.esm -CSkyrim.esm -SEskyrim_english.strings -SCskyrim_chinese.strings > skyrim.json

---

⚠️ 注意事项

.strings 文件名可能误导，请确认内容真实语言；

使用 strings 模式时，-E 和 -C 可以为同一文件；

工具不会释放堆内存，依赖程序退出时系统回收；

不附带任何原始游戏资源或翻译文件，需用户自行提供；


```

---

📄 开源协议

本工具使用 MIT 协议开源，欢迎使用、参考、修改、改进。

---

👤 作者

RainMyst

欢迎在 B 站或 GitHub 留言交流。

---
通过网盘分享的文件：wemap.zip
链接: https://pan.baidu.com/s/1laWlRrKsE-k11tN0mARexg?pwd=weap 提取码: weap
--来自百度网盘超级会员v4的分享
使用方法见视频与压缩包中的说明与提醒
