#include <iostream>
#include <string>
#include <vector>
using namespace std;

class DadosPessoa {
protected:
    string nome;
    string numBI;
    int anoNascimento;

public:
    DadosPessoa(string nome, string numBI, int anoNascimento)
        : nome(nome), numBI(numBI), anoNascimento(anoNascimento) {}

    string getNome() const { return nome; }
    string getNumBI() const { return numBI; }
    int getAnoNascimento() const { return anoNascimento; }
};

class Aluno : public DadosPessoa {
private:
    string escola;
    string idMatricula;
    string contacto;

public:
    Aluno(string nome, string numBI, int anoNascimento, string escola, string idMatricula, string contacto)
        : DadosPessoa(nome, numBI, anoNascimento), escola(escola), idMatricula(idMatricula), contacto(contacto) {}

    string getEscola() const { return escola; }
    string getIdMatricula() const { return idMatricula; }
    string getContacto() const { return contacto; }

    string infoAluno() const {
        return "Escola: " + this->escola + ", Id Matricula: " + this->idMatricula + ", Email: " + this->contacto;
    }

};

class ContaCartao : public DadosPessoa {
private:
    string numConta;
    bool estado;
    float saldo;

public:
    ContaCartao(string nome, string numBI, int anoNascimento, string numConta, bool estado, float saldo)
        : DadosPessoa(nome, numBI, anoNascimento), numConta(numConta), estado(estado), saldo(saldo) {}

    string getNumConta() const { return numConta; }
    bool getEstado() const { return estado; }
    float getSaldo() const { return saldo; }

    bool levantarDinheiro(float montante) {
        if (montante > 0 && saldo >= montante) {
            saldo -= montante;
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

class ContaAluno : public Aluno, public ContaCartao {
private:
    float desconto_lev;
    float bonos_dep;

public:
    ContaAluno(string nome, string numBI, int anoNascimento, string escola, string idMatricula, string contacto,
        string numConta, bool estado, float saldo, float desconto_lev, float bonos_dep)
        : Aluno(nome, numBI, anoNascimento, escola, idMatricula, contacto),
        ContaCartao(nome, numBI, anoNascimento, numConta, estado, saldo),
        desconto_lev(desconto_lev), bonos_dep(bonos_dep) {}

    float getDescontoLev() const { return this->desconto_lev; }
    float getBonosDep() const { return this->bonos_dep; }

    bool levantarDinheiro(float montante) {
        montante -= montante * this->desconto_lev;
        return ContaCartao::levantarDinheiro(montante);
    }

    bool depositarDinheiro(float montante) {
        // Corrigindo a chamada para depositarDinheiro da classe base
        return ContaCartao::depositarDinheiro(montante);
    }

    bool transferirDinheiro(float montante, ContaAluno& contaDest) {
        return ContaCartao::transferirDinheiro(montante, contaDest);
    }

};

int main() {
    vector<ContaAluno> alunos;

    alunos.push_back(ContaAluno("Joao da Silva", "123456789", 1998, "Escola ABC", "12345", "email1@gmail.com", "987654321", true, 1000.0, 0.5, 0.2));
    alunos.push_back(ContaAluno("Maria Oliveira", "987654321", 2000, "Escola XYZ", "54321", "email2@gmail.com", "123456789", true, 1500.0, 0.5, 0.2));

    int opcao;
    float montante;
    string numContaOrigem, numContaDestino;

    ContaAluno* origem = nullptr;
    ContaAluno* destino = nullptr;

    do {
        cout << "\nMenu:\n1. Ver conta\n2. Efetuar Transacao\n0. Sair\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "\nInformacoes de todas as contas:" << endl;
            for (const auto& aluno : alunos) {
                cout << "Nome: " << aluno.DadosPessoa::getNome() << endl;
                cout << "Num BI: " << aluno.DadosPessoa::getNumBI() << endl;
                cout << "Ano de Nascimento: " << aluno.DadosPessoa::getAnoNascimento() << endl;
                cout << "Info Aluno: " << aluno.infoAluno() << endl;
                cout << "Numero da Conta: " << aluno.getNumConta() << endl;
                cout << "Estado da Conta: " << (aluno.getEstado() ? "Ativaa" : "Inativa") << endl;
                cout << "Saldo Inicial: " << aluno.getSaldo() << endl;
                cout << endl;
            }
            break;
        case 2:
            int tipoTransacao;
            cout << "\nTipo de Transacao:\n1. Levantar dinheiro\n2. Depositar dinheiro\n3. Transferir dinheiro\nEscolha uma opcao: ";
            cin >> tipoTransacao;

            switch (tipoTransacao) {
            case 1:
                cout << "Digite o montante a levantar: ";
                cin >> montante;
                cout << "Digite o numero da conta: ";
                cin >> numContaOrigem;
                for (auto& aluno : alunos) {
                    if (aluno.getNumConta() == numContaOrigem) {
                        if (aluno.levantarDinheiro(montante)) {
                            cout << "Deposito efetuado com sucesso. Saldo atual: " << aluno.getSaldo() << endl;
                        }
                        else {
                            cout << "Erro ao depositar dinheiro." << endl;
                        }
                        break;
                    }
                }
                break;
            case 2:
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
