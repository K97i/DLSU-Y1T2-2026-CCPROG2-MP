<h1 align="center">Chardex</h1>
<p align="center">
    <img width="600px" src="./github-assets/chardex-logo.png"></img><br/>
    <i>(Charmander + Pokedex, working title)</i><br/><br/>
    <b> CCPROG2 S19B (T2, 2025-2026) - MP Project</b><br/>
    <i>Authors:</i> <br/>
    EBORDE, Mikaelo<br/>
    SACRAMENTO, Yvan <br/>
</p>

---

Chardex is a re-implementation of one of the most important tools in Pokemon, the Pokedex. It is a program that users can log what species one may have, with a leaderboard to incite competition to raise awareness.

<i>In line with <b>United Nations Sustainable Development Goals (SDGs) 14 (Life on Water), and 15 (Life on Land).</b></i>

# Run Locally

1. Open Powershell in this folder (`cd`, File Explorer Navigation Bar => `powershell`, right-click in folder => "Open Terminal" (Windows 11))
2. Run the following:
```ps
cls ; gcc -Wall -std=c99 -o chardex ./src/*.c ; ./chardex.exe
```