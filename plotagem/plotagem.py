import heapq  # Biblioteca para manipulação de heap
import numpy as np  # Biblioteca para manipulação de arrays e geração de dados aleatórios
import matplotlib.pyplot as plt  # Biblioteca para plotagem de gráficos

# Função para inserir em uma fila de prioridade SEM heap (mantendo a lista ordenada)
def inserir_sem_heap(fila, entrada):
    fila.append(entrada)
    fila.sort(key=lambda x: x[1], reverse=True)

# Função para inserir em uma fila de prioridade COM heap
def inserir_com_heap(fila, entrada):
    heapq.heappush(fila, (-entrada[1], entrada))

# Função para medir comparações na busca em uma fila de prioridade SEM heap
def busca_comparacoes_sem_heap(fila, valor):
    comparacoes = 0
    for entrada in fila:
        comparacoes += 1
        if entrada[2] == valor:
            break
    return comparacoes

# Função para medir comparações na busca em uma fila de prioridade COM heap
def busca_comparacoes_com_heap(fila, valor):
    comparacoes = 0
    for entrada in fila:
        comparacoes += 1
        if entrada[1][2] == valor:  # Entrada[1] porque a prioridade é armazenada com sinal invertido no heap
            break
    return comparacoes

# Função para plotar os resultados das comparações de busca
def plotar_resultados_comparacoes(tamanhos, comparacoes_sem_heap, comparacoes_com_heap):
    plt.figure(figsize=(12, 6))
    plt.plot(tamanhos, comparacoes_sem_heap, label='Fila de Prioridade SEM Heap')
    plt.plot(tamanhos, comparacoes_com_heap, label='Fila de Prioridade COM Heap')
    plt.xlabel('Tamanho da Fila')
    plt.ylabel('Média de Comparações')
    plt.title('Comparação: Número de Comparações na Busca SEM vs COM Heap')
    plt.legend()
    plt.grid(True)
    plt.show()

# Função principal
def main():
    tamanhos_dados = [10000, 20000, 30000, 40000, 50000]
    comparacoes_busca_sem_heap = []
    comparacoes_busca_com_heap = []

    for tamanho in tamanhos_dados:
        # Gerando valores e prioridades aleatórios
        valores = np.random.randint(1, tamanho + 1, tamanho)
        prioridades = np.random.randint(1, 101, tamanho)
        entradas = [(i + 1, prioridades[i], valores[i]) for i in range(tamanho)]

        # Inserção das entradas na fila SEM heap
        fila_sem_heap = []
        for entrada in entradas:
            inserir_sem_heap(fila_sem_heap, entrada)

        # Inserção das entradas na fila COM heap
        fila_com_heap = []
        for entrada in entradas:
            inserir_com_heap(fila_com_heap, entrada)

        # Gerando 100 valores aleatórios para busca
        valores_procurados = np.random.choice(valores, 100, replace=True)

        # Comparações para busca na fila SEM heap
        total_comparacoes_sem_heap = 0
        for valor in valores_procurados:
            total_comparacoes_sem_heap += busca_comparacoes_sem_heap(fila_sem_heap, valor)
        comparacoes_busca_sem_heap.append(total_comparacoes_sem_heap / 100)  # Média das comparações

        # Comparações para busca na fila COM heap
        total_comparacoes_com_heap = 0
        for valor in valores_procurados:
            total_comparacoes_com_heap += busca_comparacoes_com_heap(fila_com_heap, valor)
        comparacoes_busca_com_heap.append(total_comparacoes_com_heap / 100)  # Média das comparações

    # Plotando os resultados da média de comparações de busca
    plotar_resultados_comparacoes(tamanhos_dados, comparacoes_busca_sem_heap, comparacoes_busca_com_heap)

if __name__ == "__main__":
    main()