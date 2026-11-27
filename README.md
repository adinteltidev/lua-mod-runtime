# Lua Mod Runtime

Biblioteca C para executar scripts Lua com limite de memória, orçamento de instruções e um conjunto restrito de bibliotecas. O executável de exemplo carrega scripts Lua em formato texto e retorna zero quando o script termina com sucesso.

## Compilar e executar

É necessário ter CMake 3.16 ou superior e um compilador C. A compilação usa a cópia de Lua no repositório e funciona sem downloads.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/lua-mod-run examples/basic.lua
```

No Windows, use `build/Debug/lua-mod-run.exe` quando o gerador separar os executáveis por configuração. Para incorporar a biblioteca, use o alvo CMake `lua_mod_runtime` e a interface em `src/mods/sandbox.h`. Os limites auxiliam no controle de recursos. Para executar scripts de terceiros, considere também o isolamento no nível do processo.

## Origem e licenças

A implementação de limites em `src/mods/sandbox.c` e `src/mods/sandbox.h` foi extraída do projeto comunitário [oracles-decomp](https://github.com/kirby-letsgo/oracles-decomp), com contribuições de kirby-letsgo e Adriano Gomes Pimentel. O código da biblioteca e o executável de exemplo seguem a GPLv3. A cópia modificada de Lua mantém a licença MIT incluída em `third_party/lua/lua.h`. As alterações locais em Lua constam em `third_party/lua/README.md`.
