#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Definição da classe DadosPessoa, que contém informações básicas sobre uma pessoa.
class DadosPessoa {
protected:
    string nome;
    string numBI;
    int anoNascimento;

public:
    // Construtores da classe DadosPessoa.
    DadosPessoa() : nome(""), numBI(""), anoNascimento(0) {}
    DadosPessoa(string nome, string numBI, int anoNascimento)
        : nome(nome), numBI(numBI), anoNascimento(anoNascimento) {}

    // Métodos para acessar informações da pessoa.
    string getNome() const { return nome; }
    string getNumBI() const { return numBI; }
    int getAnoNascimento() const { return anoNascimento; }
};

// Definição da classe Aluno que herda de DadosPessoa, representando um aluno.
class Aluno : virtual public DadosPessoa {
private:
    string escola;
    string idMatricula;
    string contacto;

public:
    // Construtor da classe Aluno que também chama o construtor da classe base DadosPessoa.
    Aluno(string nome, string numBI, int anoNascimento, string escola, string idMatricula, string contacto)
        : DadosPessoa(nome, numBI, anoNascimento), escola(escola), idMatricula(idMatricula), contacto(contacto) {}

    // Métodos para acessar informações específicas do aluno.
    string getEscola() const { return escola; }
    string getIdMatricula() const { return idMatricula; }
    string getContacto() const { return contacto; }

    // Método para obter informações formatadas sobre o aluno.
    string infoAluno() const {
        return "Escola: " + getEscola() + ", Id Matricula: " + getIdMatricula() + ", Email: " + getContacto();
    }
};

// Definição da classe ContaCartao que herda de DadosPessoa, representando uma conta bancária.
class ContaCartao : virtual public DadosPessoa {
private:
    string numConta;
    bool estado;
    float saldo;

public:
    // Construtor da classe ContaCartao que também chama o construtor da classe base DadosPessoa.
    ContaCartao(string nome, string numBI, int anoNascimento, string numConta, bool estado, float saldo)
        : DadosPessoa(nome, numBI, anoNascimento), numConta(numConta), estado(estado), saldo(saldo) {}

    // Métodos para acessar informações específicas da conta bancária.
    string getNumConta() const { return numConta; }
    bool getEstado() const { return estado; }
    float getSaldo() const { return saldo; }

    // Métodos para operações bancárias como levantar, depositar e transferir dinheiro.
    bool levantarDinheiro(float montante) {
        if (montante > 0 && saldo >= montante) {
            saldo -= montante + 0.5;
            return true;
        }
        return false;
    }

    bool depositarDinheiro(float montante) {
        if (montante > 0) {
            saldo += montante;
            return true;
        }
        return false;
    }

    bool transferirDinheiro(float montante, ContaCartao& contaDest) {
        if (montante > 0 && saldo >= montante) {
            saldo -= montante;
            contaDest.depositarDinheiro(montante);
            return true;
        }
        return false;
    }
};

// Definição da classe ContaAluno que combina informações de Aluno e funcionalidades de ContaCartao.
class ContaAluno : public Aluno, public ContaCartao {
private:
    float desconto_lev;
    float bonos_dep;

public:
    // Construtor da classe ContaAluno que também chama os construtores das classes base Aluno e ContaCartao.
    ContaAluno(string nome, string numBI, int anoNascimento, string escola, string idMatricula, string contacto,
        string numConta, bool estado, float saldo, float desconto_lev, float bonos_dep)
        : DadosPessoa(nome, numBI, anoNascimento), Aluno(nome, numBI, anoNascimento, escola, idMatricula, contacto),
        ContaCartao(nome, numBI, anoNascimento, numConta, estado, saldo),
        desconto_lev(desconto_lev), bonos_dep(bonos_dep) {}

    // Métodos para acessar descontos e bônus específicos para contas de aluno.
    float getDescontoLev() const { return 0.3; }
    float getBonosDep() const { return 0.2; }

    // Sobrescrita dos métodos de levantar e depositar dinheiro para aplicar descontos e bônus.
    bool levantarDinheiro(float montante) {
        montante -= getDescontoLev();
        return ContaCartao::levantarDinheiro(montante);
    }

    bool depositarDinheiro(float montante) {
        montante += getBonosDep();
        return ContaCartao::depositarDinheiro(montante);
    }

    bool transferirDinheiro(float montante, ContaCartao& contaDest) {
        return ContaCartao::transferirDinheiro(montante, contaDest);
    }
};

// Função principal (main) onde o programa é executado.
int main() {
    // Criação de um vetor de ContaAluno para armazenar informações de alunos com contas bancárias.
    vector<ContaAluno> alunos;

    // Adição de dois alunos ao vetor, cada um com suas informações específicas.
    alunos.push_back(ContaAluno("Joao Joao", "123456789", 1998, "Escola ABC", "12345", "email1@gmail.com", "987654321", true, 1000.0, 0, 0));
    alunos.push_back(ContaAluno("Maria Maria", "987654321", 2000, "Escola XYZ", "54321", "email2@gmail.com", "123456789", true, 1500.0, 0, 0));

    int opcao;
    float montante;
    string numContaOrigem, numContaDestino;

    ContaAluno* origem = nullptr;
    ContaAluno* destino = nullptr;

    // Loop principal do programa que exibe um menu e executa operações com base na escolha do usuário.
    do {
        cout << "\nMenu:\n1. Ver conta\n2. Efetuar Transacao\n0. Sair\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            // Exibir informações de todas as contas de alunos no vetor.
            cout << "\nInformacoes de todas as contas:" << endl;
            for (const auto& aluno : alunos) {
                cout << "Nome: " << aluno.getNome() << endl;
                cout << "Num BI: " << aluno.getNumBI() << endl;
                cout << "Ano de Nascimento: " << aluno.getAnoNascimento() << endl;
                cout << "Info Aluno: " << aluno.infoAluno() << endl;
                cout << "Numero da Conta: " << aluno.getNumConta() << endl;
                cout << "Estado da Conta: " << (aluno.getEstado() ? "Ativa" : "Inativa") << endl;
                cout << "Saldo: " << aluno.getSaldo() << endl;
                cout << endl;
            }
            break;
        case 2:
            int tipoTransacao;
            cout << "\nTipo de Transacao:\n1. Levantar dinheiro\n2. Depositar dinheiro\n3. Transferir dinheiro\nEscolha uma opcao: ";
            cin >> tipoTransacao;

            switch (tipoTransacao) {
            case 1:
                // Opção para levantar dinheiro de uma conta específica.
                cout << "Digite o montante a levantar: ";
                cin >> montante;
                cout << "Digite o numero da conta: ";
                cin >> numContaOrigem;
                for (auto& aluno : alunos) {
                    if (aluno.getNumConta() == numContaOrigem) {
                        if (aluno.levantarDinheiro(montante)) {
                            cout << "Levantamento efetuado com sucesso. Saldo atual: " << aluno.getSaldo() << endl;
                        }
                        else {
                            cout << "Erro ao levantar dinheiro." << endl;
                        }
                        break;
                    }
                }
                break;
            case 2:
                // Opção para depositar dinheiro em uma conta específica.
                cout << "Digite o montante a depositar: ";
                cin >> montante;
                cout << "Digite o numero da conta: ";
                cin >> numContaOrigem;
                for (auto& aluno : alunos) {
                    if (aluno.getNumConta() == numContaOrigem) {
                        if (aluno.depositarDinheiro(montante)) {
                            cout << "Deposito efetuado com sucesso. Saldo atual: " << aluno.getSaldo() << endl;
                        }
                        else {
                            cout << "Erro ao depositar dinheiro." << endl;
                        }
                        break;
                    }
                }
                break;
            case 3:
                // Opção para transferir dinheiro entre duas contas.
                cout << "Digite o montante a transferir: ";
                cin >> montante;
                cout << "Digite o numero da conta de origem: ";
                cin >> numContaOrigem;
                cout << "Digite o numero da conta destino: ";
                cin >> numContaDestino;

                for (auto& aluno : alunos) {
                    if (aluno.getNumConta() == numContaOrigem) {
                        origem = &aluno;
                    }
                    if (aluno.getNumConta() == numContaDestino) {
                        destino = &aluno;
                    }
                }
                if (origem != nullptr && destino != nullptr) {
                    if (origem->transferirDinheiro(montante, *destino)) {
                        cout << "Transferencia efetuada com sucesso." << endl;
                        cout << "Saldo atual na conta origem: " << origem->getSaldo() << endl;
                        cout << "Saldo atual na conta destino: " << destino->getSaldo() << endl;
                    }
                    else {
                        cout << "Erro ao transferir dinheiro." << endl;
                    }
                }
                else {
                    cout << "Contas nao encontradas." << endl;
                }
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
            }
            break;
        case 0:
            cout << "Saindo do programa." << endl;
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}
