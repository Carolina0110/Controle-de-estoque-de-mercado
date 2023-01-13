#include <stdio.h>

struct estrutura{
  char produto[40];
  char fornecedor[40];
  int quantidade;
  float preco;
};

int verifica(char *s1, char *s2)
{
    for(int i=0; i<40; i++)
    {
        if (s1[i]=='\0' && s2[i]=='\0')
        {
            return 0;
        }
        if (s1[i] != s2[i])
        {
            return 1;
        }
    }
}

//1
void EntradaProdutos(struct estrutura *p){
  FILE *arq_txt;
   arq_txt = fopen ("arq.txt","a");
    if(arq_txt == NULL){
        printf("Erro!\n");
        exit(0);
    }

  printf("\nDigite o nome do produto:");
  getchar();
  gets((*p).produto);
  printf("\nDigite o fornecedor do produto:");
  gets((*p).fornecedor);
  printf("\nDigite a quantidade do produto:");
 //getchar();
  scanf("%d",&(*p).quantidade);
  printf("\nDigite o preço do produto:");
  scanf("%f",&(*p).preco);
  fwrite(p,sizeof(struct estrutura),1,arq_txt);
  fclose(arq_txt);
  
  system("clear");
  printf("Produto cadastrado com sucesso!\n");
}

//2
void ListaProdutos(struct estrutura *p){
    FILE *arq_txt;
    int i;

    arq_txt = fopen("arq.txt","r");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    for(;;)
    {
        i=fread(p, sizeof(struct estrutura), 1, arq_txt);

        if(i==0)
        {
            break;
        }

        if (p->produto[0] != '\0')
        {
            printf("\nProduto: %s", p->produto);
            printf("\nFornecedor: %s", p->fornecedor);
            printf("\nQuantidade: %d", p->quantidade);
            printf("\nPreço: R$ %.2f\n", p->preco);
        }
    }
    fclose(arq_txt);
}

//3
int PesquisaProduto(struct estrutura *p){
    FILE *arq_txt;
    char produto1[40];
    int i, z, cont = 0;

    arq_txt = fopen("arq.txt","r");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    getchar();
    printf("\nDigite o nome do produto a ser procurado: ");
    gets(produto1);

    for(;;)
    {
        i=fread(p, sizeof(struct estrutura), 1, arq_txt);

        if(i==0)
        {
            break;
        }
        z=verifica(produto1,p->produto);

        if(z == 0)
        {
            if(p->produto[0] != '\0')
            {
                printf("\nREGISTRO ENCONTRADO!");
                printf("\nProduto: %s", p->produto);
                printf("\nFornecedor: %s", p->fornecedor);
                printf("\nQuantidade: %d", p->quantidade);
                printf("\nPreço: R$ %.2f\n", p->preco);
                return cont;
            }
        }
        cont++;
    }

    printf("\nNENHUM REGISTRO ENCONTRADO!\n");
    return -1;
    fclose(arq_txt);
}

//4
void PesquisaFornecedor(struct estrutura *p){
    FILE *arq_txt;
    char f[40];
    int i, z, cont=0;

    arq_txt = fopen("arq.txt","r");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    getchar();
    printf("\nDigite o fornecedor do produto a ser procurado: ");
    gets(f);

    for(;;)
    {
        z=fread(p, sizeof(struct estrutura), 1, arq_txt);

        if(z==0)
        {
            break;
        }

        i=verifica(f,p->fornecedor);

        if(i == 0)
        {
            if(p->produto[0] != '\0')
            {
                printf("\nREGISTRO ENCONTRADO!");
                printf("\nProduto: %s", p->produto);
                printf("\nFornecedor: %s", p->fornecedor);
                printf("\nQuantidade: %d", p->quantidade);
                printf("\nPreço: R$ %.2f\n", p->preco);
                cont++;
            }
        }
    }
    if(cont == 0)
        printf("\nNENHUM REGISTRO ENCONTRADO!\n");
    fclose(arq_txt);
}

//5
void PesquisaProdutoFP(struct estrutura *p){
    FILE *arq_txt;
    int z, cont = 0;
    float min, max;

    arq_txt = fopen("arq.txt","r");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    printf("\nPESQUISA POR FAIXA DE PRECO:\n");
    printf("\nDigite uma faixa de preço inicial(min): ");
    scanf("%f", &min);

    do
    {
        printf("Digite uma faixa de preço final (max): ");
        scanf("%f", &max);
        if(min > max)
            printf("A faica de preço final deve ser menor que a inicial, tente novamente.\n");
    }while(min > max);

    for(;;)
    {
        z=fread(p, sizeof(struct estrutura), 1, arq_txt);

        if(z==0)
        {
            break;
        }

        if(p->produto[0] != '\0')
        {
            if(p->preco >= min && p->preco <= max)
            {
                printf("\nREGISTRO ENCONTRADO!");
                printf("\nProduto: %s", p->produto);
                printf("\nFornecedor: %s", p->fornecedor);
                printf("\nQuantidade: %d", p->quantidade);
                printf("\nPreço: R$ %.2f\n", p->preco);
                cont++;
            }
        }
    }
    if(cont == 0)
        printf("\nNENHUM REGISTRO ENCONTRADO!\n");
    fclose(arq_txt);
}

//6
void AlteraQuant(struct estrutura *p){
    FILE *arq_txt;
    int r = 0;
    int Bytes = 0;
    int nquant;
    r = PesquisaProduto(p);

    if(r == -1)
    {
        printf("%d", r);
        return;
    }

    printf("\nALTERAÇÃO DE QUANTIDADE:\n");
    printf("Nova quantidade: ");
    scanf("%d", &nquant);

    arq_txt = fopen("arq.txt","r+");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    Bytes = sizeof(*p) * r;
    fseek(arq_txt,Bytes,0);
    fread(p,sizeof(*p),1,arq_txt);

    p->quantidade = nquant;

    printf("\nQUANTIDADE ALTERADA COM SUCESSO!\n");
    fseek(arq_txt,Bytes,0);
    fwrite(p,sizeof(*p),1,arq_txt);

    fclose(arq_txt);
}

//7
void AlteraPreçoPNomeC(struct estrutura *p){
    FILE *arq_txt;
    int r = 0;
    int Bytes = 0;
    float npreco;
    r = PesquisaProduto(p);

    if(r == -1)
    {
        printf("%d", r);
        return;
    }

    printf("\nALTERAÇÃO DE PREÇO:\n");
    printf("Novo preço: R$ ");
    scanf("%f", &npreco);

    arq_txt = fopen("arq.txt","r+");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    Bytes = sizeof(*p) * r;
    fseek(arq_txt,Bytes,0);
    fread(p,sizeof(*p),1,arq_txt);

    p->preco = npreco;

    printf("\nPREÇO ALTERADO COM SUCESSO!\n");
    fseek(arq_txt,Bytes,0);
    fwrite(p,sizeof(*p),1,arq_txt);

    fclose(arq_txt);

}

//8
// CORRIGIR
void AlteraProdutoPNomeC(struct estrutura *p){
    FILE *arq_txt;
    int r = 0;
    int Bytes = 0;
    r = PesquisaProduto(p);

    if(r == -1)
    {
        return;
    }

    arq_txt = fopen("arq.txt","r+");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    Bytes = sizeof(*p) * r;
    fseek(arq_txt,Bytes,0);
    fread(p,sizeof(*p),1,arq_txt);

    printf("\nALTERACAO DE PRODUTO:");
    printf("\nProduto: ");
    gets((*p).produto);
    printf("Fornecedor: ");
    gets((*p).fornecedor);
    printf("Quantidade: ");
    scanf("%d", &(*p).quantidade);
    printf("Preço: R$ ");
    scanf("%f", &(*p).preco);
    getchar();

    printf("\nPRODUTO ALTERADO COM SUCESSO!\n");
    fseek(arq_txt,Bytes,0);
    fwrite(p,sizeof(*p),1,arq_txt);

    fclose(arq_txt);
}

//9
void ExcluiProdutoPNomeC(struct estrutura *p){
    FILE *arq_txt;
    int r = 0, botão;
    int Bytes = 0;
    r = PesquisaProduto(p);

    if(r == -1)
    {
        return;
    }

    printf("\nDeseja excluir este produto? 1 = [SIM] Outro caracter [NAO]\n--> ");
    scanf("%d", &botão);
    if(botão != 1)
    {
        return;
    }

    arq_txt = fopen("arq.txt","r+");
    if(arq_txt == NULL)
    {
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(0);
    }

    Bytes = sizeof(*p) * r;
    fseek(arq_txt,Bytes,0);
    fread(p,sizeof(*p),1,arq_txt);

    p->produto[0] = '\0';

    printf("\nPRODUTO EXCLUIDO COM SUCESSO!\n");
    fseek(arq_txt,Bytes,0);
    fwrite(p,sizeof(*p),1,arq_txt);

    fclose(arq_txt);
}



int main(void) {
  struct estrutura produto;
  int opcao;
system("clear");

    for(;;){
      printf("\nDigite uma opção:\n(1) Cadastrar produtos.\n(2) Lista todos os produtos na tela.\n(3) Pesquisar produto por nome completo.\n(4) Pesquisar por fornecedor completo.\n(5) Pesquisa produtos por faixa de preço.\n(6) Altera quantidade em estoque pesquisando pelo nome.\n(7) Altera preço de um produto pesquisando pelo nome completo.\n(8) Altera produto pesquisando pelo nome completo.\n(9)Excluir produto pesquisando pelo nome completo.\n(10) Sair.\n");
      scanf("%d",&opcao);
      
        switch(opcao){
          case 1:
            EntradaProdutos(&produto);
          break;

          case 2:
            ListaProdutos(&produto);
          break;

          case 3:
            PesquisaProduto(&produto);
          break;

          case 4:
            PesquisaFornecedor(&produto);
          break;

          case 5:
            PesquisaProdutoFP(&produto);
          break; 

         case 6:
           AlteraQuant(&produto);
           break;

        case 7:  
         AlteraPreçoPNomeC(&produto);
         break;

        case 8:
        AlteraProdutoPNomeC(&produto);
        break;
              
        case 9:
        ExcluiProdutoPNomeC(&produto);
        break; 

        case 10:
        exit(0);
        break;

        default:
        printf("Opcao invalida!\n");
        break;
        }
    }

}