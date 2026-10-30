# Redução de Suíte de Testes

**Autores:** André Luiz Caillot de Oliveira Filho, Davi Fernandes, Vitor Janzkovski Cardoso de Mello

**Disciplina:** AE43CP - Algoritmos e Estruturas de Dados 2 - UTFPR

---

## Descrição do problema

Em software, um **requisito** descreve um comportamento que o sistema deve atender, e um **teste** verifica um ou mais requisitos. Um mesmo teste pode cobrir vários requisitos, e um mesmo requisito pode ser coberto por vários testes. Quando isso acontece, existe **redundância de cobertura**.

Suítes de testes grandes demoram mais para serem executadas e analisadas. A **redução** busca selecionar um subconjunto dos testes existentes que continue cobrindo **todos** os requisitos, usando o menor número possível de testes.

Este projeto recebe uma matriz binária de cobertura (linhas = testes, colunas = requisitos) e compara duas estratégias de seleção. Trata-se de uma instância do clássico problema de **cobertura de conjuntos** (*Set Cover*).

> O programa não executa testes reais nem mede cobertura de código. O valor 1 na matriz é uma simplificação: indica que o teste fornece a cobertura necessária para o requisito, sem garantir a detecção de defeitos.

---

## Objetivos e especificações do projeto

O objetivo é implementar e comparar duas estratégias de redução de suíte de testes.

* **Linguagem:** C
* **Dependências:** Compilador C (gcc 7+ ou clang)
* **Capacidades principais:**
  * Leitura e validação da entrada (quantidades, identificadores e valores binários).
  * Verificação de requisitos impossíveis de cobrir.
  * Estratégia **exata por força bruta**, que garante a quantidade mínima de testes.
  * Estratégia **gulosa**, que escolhe a cada passo o teste com maior ganho de cobertura.
  * Comparação entre as duas seleções.

---

## Formato da entrada

A entrada vem pela entrada padrão ou por um arquivo de texto:

```
n m
R1 R2 ... Rm
T1 v11 v12 ... v1m
...
Tn vn1 vn2 ... vnm
```

* Primeira linha: quantidade de testes `n` (1 a 15) e de requisitos `m` (1 a 20).
* Segunda linha: identificadores dos requisitos, na ordem das colunas.
* Próximas `n` linhas: identificador do teste seguido de `m` valores binários.
* Identificadores não podem conter espaços nem se repetir dentro do próprio conjunto.

**Exemplo:**

```
4 5
R1 R2 R3 R4 R5
T1 1 1 0 0 0
T2 0 0 1 1 0
T3 0 0 0 0 1
T4 1 0 1 0 1
```

---

## Lógica do programa (como funciona?)

1. **Leitura e validação:** lê a matriz e confere quantidades, identificadores e valores. Se algo violar o contrato, informa o motivo e encerra sem executar as estratégias.
2. **Checagem de viabilidade:** verifica se cada requisito aparece em pelo menos um teste. Se houver coluna só com zeros, lista esses requisitos na ordem da entrada e não executa as estratégias.
3. **Força bruta:** examina os subconjuntos de testes e retorna uma seleção válida com o menor número de testes. Os identificadores saem na ordem da entrada.
4. **Guloso:**
   * A cada passo, escolhe o teste que cobre a maior quantidade de requisitos **ainda não cobertos**.
   * Recalcula a contribuição de cada teste após cada escolha.
   * Em caso de empate, escolhe o primeiro teste na ordem da entrada.
   * Os identificadores saem na ordem em que foram escolhidos.
5. **Comparação:** compara as quantidades das duas seleções e informa quantos testes adicionais o guloso usou, se houver diferença.

---

## Modelagem matemática

### Seleção válida

Sejam `R = {r1, ..., rm}` os requisitos, `T = {t1, ..., tn}` os testes e `C(ti)` o conjunto de requisitos cobertos por `ti`. Uma seleção `S ⊆ T` é válida quando:

$$\bigcup_{t_i \in S} C(t_i) = R$$

### Custo e solução ótima

Cada teste tem custo 1, então o custo de `S` é $|S|$. Uma solução ótima é uma seleção válida com o menor $|S|$ possível.

### Regra gulosa

$$t^* = \arg\max_{t_i \notin S} \left| C(t_i) \setminus \bigcup_{t_j \in S} C(t_j) \right|$$

---

## Como executar o projeto

## Como compilar e executar
 
### 1. Clonar o repositório
 
```bash
git clone https://github.com/alcdof/reducao-suite-testes.git
cd reducao-suite-testes
```
 
### 2. Compilar
 
```bash
gcc -std=c99 -Wall -Wextra -O2 -o reducao src/*.c
```
 
### 3. Executar
 
A entrada é lida pela entrada padrão. Para usar um arquivo:
 
```bash
./reducao < casos/referencia.txt
```
 
Para digitar a entrada manualmente:
 
```bash
./reducao
```
 
No Windows (PowerShell/MinGW), o executável é `reducao.exe`.
 
---
## Saída esperada

Para a entrada de referência:

```
Forca bruta: 3 testes, T1 T2 T3
Guloso: 3 testes, T4 T1 T2
Quantidade do guloso igual ao minimo: sim
Testes adicionais: 0
```

Se a cobertura completa for impossível, o programa lista os requisitos que não aparecem em nenhum teste e não mostra seleção parcial.

---

## Estrutura do repositório

```
reducao-suite-testes/
├── src/          código das estratégias
├── casos/        arquivos de texto com as entradas de teste
├── docs/         relatório e análise
└── README.md
```

---

## Casos de teste

Cada caso fica em `casos/`, com entrada, saída obtida e verificação manual da cobertura. Os resultados podem ser verificados no relatório, disponível em `docs/relatorio.pdf`.

| Caso | Descrição |
|------|-----------|
| `referencia.txt` | Matriz do enunciado |
| `redundancia.txt` | Sobreposição e redundância entre coberturas |
| `impossivel.txt` | Pelo menos um requisito sem cobertura |
| `limite.txt` | Um teste e um requisito |

---

## Análise: o guloso sempre é ótimo?

[Preencher com a conclusão do grupo, acompanhada de demonstração ou de um contraexemplo. Se usar contraexemplo, incluir a matriz e a saída das duas estratégias. Link para o relatório completo em `docs/relatorio.pdf`.]

---

## Divisão de tarefas

| Integrante | Responsabilidade | Branch |
|------------|------------------|--------|
| André Caillot | Leitura e validação da entrada | `feature/validacao-entrada` |
| Vitor Janzkovski | Força bruta | `feature/forca-bruta` |
| André Caillot | Guloso | `feature/guloso` |
| Davi Fernandes | Casos de teste e documentação | `test/casos-de-teste`, `docs/relatorio` |

---

## Aviso

Este projeto tem fins educacionais. O modelo de cobertura é uma simplificação e não substitui a análise de cobertura real de um software.

---

## Contato

* **André Caillot Filho** - [GitHub](https://github.com/alcdof) - [andreluizfilho@alunos.utfpr.edu.br](mailto:andreluizfilho@alunos.utfpr.edu.br)
* **Davi Fernandes** - [GitHub](https://github.com/davifern4ndes) - [davfer@alunos.utfpr.edu.br](mailto:davfer@alunos.utfpr.edu.br)
* **Vitor Janzkovski** - [GitHub](https://github.com/Janzkovski03) - [vitorm.2007@alunos.utfpr.edu.br](mailto:vitorm.2007@alunos.utfpr.edu.br)
