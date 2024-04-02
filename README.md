# Exercicio LP

## Classes

### DadosPessoa
Classe base que armazena informações básicas de uma pessoa.
- Atributos:
  - nome: string
  - numBI: string
  - anoNascimento: int
- Métodos:
  - DadosPessoa(nome: string, numBI: string, anoNascimento: int): Construtor para inicializar os atributos da classe.
  - getNome(): Retorna o nome da pessoa.
  - getNumBI(): Retorna o número do Bilhete de Identidade da pessoa.
  - getAnoNascimento(): Retorna o ano de nascimento da pessoa.

### Aluno
Classe derivada de DadosPessoa que representa um aluno.
- Atributos:
  - escola: string
  - idMatricula: string
  - contacto: string
- Métodos:
  - Aluno(nome: string, numBI: string, anoNascimento: int, escola: string, idMatricula: string, contacto: string): Construtor para inicializar os atributos da classe.
  - getEscola(): Retorna o nome da escola do aluno.
  - getIdMatricula(): Retorna o número de matrícula do aluno.
  - getContacto(): Retorna o contacto do aluno.
  - infoAluno(): Retorna uma string com informações sobre o aluno.

### ContaCartao
Classe derivada de DadosPessoa que representa uma conta de cartão.
- Atributos:
  - numConta: string
  - estado: bool
  - saldo: float
- Métodos:
  - ContaCartao(nome: string, numBI: string, anoNascimento: int, numConta: string, estado: bool, saldo: float): Construtor para inicializar os atributos da classe.
  - getNumConta(): Retorna o número da conta.
  - getEstado(): Retorna o estado da conta (ativo ou inativo).
  - getSaldo(): Retorna o saldo da conta.
  - levantarDinheiro(montante: float): Realiza um levantamento de dinheiro da conta.
  - depositarDinheiro(montante: float): Realiza um depósito de dinheiro na conta.
  - transferirDinheiro(montante: float, contaDest: ContaCartao&): Transfere dinheiro para outra conta.

### ContaAluno
Classe que combina as funcionalidades de Aluno e ContaCartao.
- Atributos:
  - desconto_lev: float
  - bonos_dep: float
- Métodos:
  - ContaAluno(nome: string, numBI: string, anoNascimento: int, escola: string, idMatricula: string, contacto: string, numConta: string, estado: bool, saldo: float, desconto_lev: float, bonos_dep: float): Construtor para inicializar os atributos da classe.
  - getDescontoLev(): Retorna o desconto para levantamento.
  - getBonosDep(): Retorna o bônus para depósito.
  - levantarDinheiro(montante: float): Realiza um levantamento de dinheiro com desconto.
  - depositarDinheiro(montante: float): Realiza um depósito de dinheiro.
  - transferirDinheiro(montante: float, contaDest: ContaAluno&): Transfere dinheiro para outra conta de aluno.

## Funcionalidades do Programa
1. Criação e manipulação de contas de alunos, permitindo operações como levantar dinheiro, depositar dinheiro e transferir dinheiro entre contas.
2. Apresentação de informações sobre as contas, incluindo detalhes dos alunos associados às contas.
3. Utiliza um menu para interação com o usuário, permitindo escolher diferentes operações e interagir com o sistema de gerenciamento de contas.

## Observações
- O programa não inclui tratamento avançado de exceções ou validação aprofundada dos dados de entrada. Recomenda-se fornecer entradas válidas para obter o funcionamento correto do programa.

**Data:** 02/04/2024
