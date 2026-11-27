# Plano de publicação

1. **Extrair a infraestrutura Lua.** Reutilizar o executor e os limites de recursos, incluir um exemplo genérico e compilar a partir de uma árvore independente, sem depender de arquivos do port. Etapa implementada neste repositório.
2. **Revisar o conteúdo a publicar.** Conferir a origem e a licença dos arquivos versionados e usar nome próprio. Esta edição contém código-fonte da infraestrutura Lua, suas dependências e o exemplo.
3. **Avaliar um build local do port completo.** Inventariar as rotinas que podem ser geradas da ROM e as que foram reescritas à mão. Para um modelo de compilação local, o usuário precisa conseguir construir a versão usando suas entradas locais e ferramentas redistribuíveis. O fluxo precisa ser validado com um checkout limpo e comparado aos testes de comportamento do port. O runtime desta edição pode ser usado como dependência desse trabalho.
4. **Revisar a distribuição do port completo.** Antes de disponibilizar fonte ou releases, conferir a origem do que foi incluído nos binários e a autorização para distribuir código derivado, traduções e material dos jogos.

A edição disponível aqui executa scripts Lua genéricos. A API específica do jogo, as regras de gameplay, os pacotes de tradução e a compilação local do port completo ficam fora desta entrega.
