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
    DadosPessoa() {
        nome = "";
        numBI = "";
        anoNascimento = 0;
    }

    DadosPessoa(string nome, string numBI, int anoNascimento) {
        this->nome = nome;
        this->numBI = numBI;
        this->anoNascimento = anoNascimento;
    }

    string getNome() const { return nome; }
    string getNumBI() const { return numBI; }
    int getAnoNascimento() const { return anoNascimento; }

    void setNome(const string& n) { nome = n; }
    void setNumBI(const string& bi) { numBI = bi; }
    void setAnoNascimento(int ano) { anoNascimento = ano; }
};

class Aluno : virtual public DadosPessoa {
private:
    string escola;
    string idMatricula;
    string contacto;

public:
    Aluno(string nome, string numBI, int anoNascimento, string escola, string idMatricula, string contacto)
        : DadosPessoa(nome, numBI, anoNascimento) {
        this->escola = escola;
        this->idMatricula = idMatricula;
        this->contacto = contacto;
    }

    string getEscola() const { return escola; }
    string getIdMatricula() const { return idMatricula; }
    string getContacto() const { return contacto; }

    void setEscola(const string& e) { escola = e; }
    void setIdMatricula(const string& id) { idMatricula = id; }
    void setContacto(const string& c) { contacto = c; }

    string infoAluno() const {
        return "Escola: " + getEscola() + ", Id Matricula: " + getIdMatricula() + ", Email: " + getContacto();
    }
};

class ContaCartao : virtual public DadosPessoa {
private:
    string numConta;
    bool estado;
    float saldo;

public:
    ContaCartao(string nome, string numBI, int anoNascimento, string numConta, bool estado, float saldo)
        : DadosPessoa(nome, numBI, anoNascimento) {
        this->numConta = numConta;
        this->estado = estado;
        this->saldo = saldo;
    }

    string getNumConta() const { return numConta; }
    bool getEstado() const { return estado; }
    float getSaldo() const { return saldo; }

    void setNumConta(const string& nc) { numConta = nc; }
    void setEstado(bool est) { estado = est; }
    void setSaldo(float s) { saldo = s; }

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

class ContaAluno : public Aluno, public ContaCartao {
private:
    float desconto_lev;
    float bonos_dep;

public:
    ContaAluno(string nome, string numBI, int anoNascimento, string escola, string idMatricula, string contacto,
        string numConta, bool estado, float saldo, float desconto_lev, float bonos_dep)
        : DadosPessoa(nome, numBI, anoNascimento), Aluno(nome, numBI, anoNascimento, escola, idMatricula, contacto),
        ContaCartao(nome, numBI, anoNascimento, numConta, estado, saldo) {
        this->desconto_lev = desconto_lev;
        this->bonos_dep = bonos_dep;
    }

    float getDescontoLev() const { return 0.3; }
    float getBonosDep() const { return 0.2; }

    void setDescontoLev(float desconto) { desconto_lev = desconto; }
    void setBonosDep(float bonus) { bonos_dep = bonus; }

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

void menu(vector<ContaAluno>& alunos) {
    int opcao;
    int index;
    int editOption;
    string novoNome;
    float novoSaldo;
    string numContaOrigem, numContaDestino;
    int indiceOrigem = -1, indiceDestino = -1;

    do {
        cout << "\nMenu:\n1. Ver conta\n2. Efetuar Transacao\n3. Editar dados\n0. Sair\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "\nInformacoes de todas as contas:" << endl;
            for (int i = 0; i < alunos.size(); ++i) {
                cout << i << ". Nome: " << alunos[i].getNome() << endl;
                cout << "   Numero BI: " << alunos[i].getNumBI() << endl;
                cout << "   Ano de Nascimento: " << alunos[i].getAnoNascimento() << endl;
                cout << "   Escola: " << alunos[i].infoAluno() << endl;
                cout << "   Numero da Conta: " << alunos[i].getNumConta() << endl;
                cout << "   Estado da Conta: " << (alunos[i].getEstado() ? "Ativa" : "Inativa") << endl;
                cout << "   Saldo: " << alunos[i].getSaldo() << endl;
                cout << endl;
            }

            break;
        case 2:
            int tipoOperacao;
            float valor;
            

            cout << "\nEscolha o tipo de operacao:\n1. Levantamento\n2. Deposito\n3. Transferencia\nOpcao: ";
            cin >> tipoOperacao;

            switch (tipoOperacao) {
            case 1:
                cout << "Digite o numero da conta para levantamento: ";
                cin >> numContaOrigem;
                for (int i = 0; i < alunos.size(); ++i) {
                    if (alunos[i].getNumConta() == numContaOrigem) {
                        cout << "Digite o valor a ser retirado: ";
                        cin >> valor;
                        if (alunos[i].levantarDinheiro(valor)) {
                            cout << "Levantamento realizado com sucesso!" << endl;
                            cout << "Saldo atual: " << alunos[i].getSaldo() << endl;
                        }
                        else {
                            cout << "Saldo insuficiente para o levantamento!" << endl;
                        }
                        break;
                    }
                }
                break;
            case 2:
                cout << "Digite o numero da conta para deposito: ";
                cin >> numContaOrigem;
                for (int i = 0; i < alunos.size(); ++i) {
                    if (alunos[i].getNumConta() == numContaOrigem) {
                        cout << "Digite o valor a ser depositado: ";
                        cin >> valor;
                        if (alunos[i].depositarDinheiro(valor)) {
                            cout << "Deposito realizado com sucesso!" << endl;
                            cout << "Saldo atual: " << alunos[i].getSaldo() << endl;
                        }
                        else {
                            cout << "Valor invalido para deposito!" << endl;
                        }
                        break;
                    }
                }
                break;
            case 3:
                cout << "Digite o numero da conta de origem para transferencia: ";
                cin >> numContaOrigem;
                cout << "Digite o numero da conta de destino para transferencia: ";
                cin >> numContaDestino;

                
                for (int i = 0; i < alunos.size(); ++i) {
                    if (alunos[i].getNumConta() == numContaOrigem) {
                        indiceOrigem = i;
                    }
                    if (alunos[i].getNumConta() == numContaDestino) {
                        indiceDestino = i;
                    }
                    if (indiceOrigem != -1 && indiceDestino != -1) {
                        break;
                    }
                }

                if (indiceOrigem != -1 && indiceDestino != -1) {
                    cout << "Digite o valor a ser transferido: ";
                    cin >> valor;
                    if (alunos[indiceOrigem].transferirDinheiro(valor, alunos[indiceDestino])) {
                        cout << "Transferencia realizada com sucesso!" << endl;
                        cout << "Saldo na conta origem: " << alunos[indiceOrigem].getSaldo() << endl;
                        cout << "Saldo na conta destino: " << alunos[indiceDestino].getSaldo() << endl;
                    }
                    else {
                        cout << "Saldo insuficiente para a transferencia!" << endl;
                    }
                }
                else {
                    cout << "Conta de origem ou conta de destino invalida para a transferencia!" << endl;
                }
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
            }
            break;
        case 3:
            cout << "\nDigite o indice do aluno que deseja editar: ";
            cin >> index;

            if (index >= 0 && index < alunos.size()) {
                cout << "Escolha o que deseja editar:\n1. Nome\nOpcao: ";
                cin >> editOption;

                switch (editOption) {
                case 1:
                    cout << "Digite o novo nome: ";
                    cin.ignore(); // Limpar o buffer de entrada
                    getline(cin, novoNome);
                    alunos[index].setNome(novoNome);
                    cout << "Nome atualizado com sucesso!" << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                    break;
                }
            }
            else {
                cout << "Indice invalido!" << endl;
            }
            break;
        case 0:
            cout << "Saindo do programa." << endl;
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            break;
        }
    } while (opcao != 0);
}

int main() {
    vector<ContaAluno> alunos;

    alunos.push_back(ContaAluno("Joao Joao", "123456789", 1998, "Escola ABC", "12345", "email1@gmail.com", "987654321", true, 1000.0, 0, 0));
    alunos.push_back(ContaAluno("Maria Maria", "987654321", 2000, "Escola XYZ", "54321", "email2@gmail.com", "123456789", true, 1500.0, 0, 0));

    menu(alunos);

    return 0;
}
