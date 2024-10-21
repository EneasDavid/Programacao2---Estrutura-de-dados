import heapq  # Biblioteca para manipulação de heap
import time  # Para medir o tempo de execução
import numpy as np  # Biblioteca para manipulação de arrays e geração de dados aleatórios
import matplotlib.pyplot as plt  # Biblioteca para plotagem de gráficos

# Função para inserir em uma fila de prioridade SEM heap (mantendo a lista ordenada)
def inserir_sem_heap(fila, entrada):
    fila.append(entrada)
    # Ordena pela prioridade em ordem decrescente
    fila.sort(key=lambda x: x[1], reverse=True)

# Função para inserir em uma fila de prioridade COM heap
def inserir_com_heap(fila, entrada):
    # Usamos -entrada[1] para simular a prioridade decrescente (heapq é min-heap)
    heapq.heappush(fila, (-entrada[1], entrada))

# Função para medir o tempo de busca em uma fila de prioridade SEM heap
def busca_sem_heap(fila, valor):
    inicio = time.time()
    for entrada in fila:
        if entrada[2] == valor:
            break
    return time.time() - inicio

# Função para medir o tempo de busca em uma fila de prioridade COM heap
def busca_com_heap(fila, valor):
    inicio = time.time()
    for entrada in fila:
        if entrada[1][2] == valor:  # Entrada[1] porque estamos armazenando a prioridade negada no heap
            break
    return time.time() - inicio

# Função para plotar os resultados do benchmark de busca
def plotar_resultados_busca(tamanhos, tempos_sem_heap, tempos_com_heap):
    plt.figure(figsize=(12, 6))
    plt.plot(tamanhos, tempos_sem_heap, label='Fila de Prioridade SEM Heap')
    plt.plot(tamanhos, tempos_com_heap, label='Fila de Prioridade COM Heap')
    plt.xlabel('Tamanho da Fila')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.title('Comparação: Busca em Fila de Prioridade SEM vs COM Heap')
    plt.legend()
    plt.show()

# Função principal
def main():
    tamanhos_dados = [10000, 20000, 30000, 40000, 50000]
    tempos_busca_sem_heap = []
    tempos_busca_com_heap = []

    for tamanho in tamanhos_dados:
        # Gerando valores aleatórios (valor varia de 1 até o tamanho da fila)
        valores = np.random.randint(1, tamanho + 1, tamanho)
        
        # Gerando prioridades aleatórias (prioridade varia de 1 até 100)
        prioridades = np.random.randint(1, 101, tamanho)

        # Gerando entradas {posição, prioridade, valor}
        entradas = [(i + 1, prioridades[i], valores[i]) for i in range(tamanho)]

        # Inserção das entradas na fila SEM heap
        fila_sem_heap = []
        for entrada in entradas:
            inserir_sem_heap(fila_sem_heap, entrada)

        # Inserção das entradas na fila COM heap
        fila_com_heap = []
        for entrada in entradas:
            inserir_com_heap(fila_com_heap, entrada)

        # Exibindo os primeiros 5 itens da fila COM heap
        print(f"Fila de prioridade COM heap (tamanho {tamanho}):")
        for i, valor in enumerate(fila_com_heap[:5]):
            print(f"Posição {i+1}: Prioridade {-valor[0]} Valor {valor[1][2]}")  # Mostrando a prioridade e valor corretos
        print("\n")

        # Exibindo os primeiros 5 itens da fila SEM heap
        print(f"Fila de prioridade SEM heap (tamanho {tamanho}):")
        for i, valor in enumerate(fila_sem_heap[:5]):
            print(f"Posição {i+1}: Prioridade {valor[1]} Valor {valor[2]}")
        print("\n")

        # Gerando 100 valores aleatórios a serem buscados
        valores_procurados = np.random.choice(valores, 100, replace=True)

        # Medindo o tempo de busca na fila SEM heap
        tempo_total_sem_heap = 0
        for valor in valores_procurados:
            tempo_total_sem_heap += busca_sem_heap(fila_sem_heap, valor)
        tempos_busca_sem_heap.append(tempo_total_sem_heap)

        # Medindo o tempo de busca na fila COM heap
        tempo_total_com_heap = 0
        for valor in valores_procurados:
            tempo_total_com_heap += busca_com_heap(fila_com_heap, valor)
        tempos_busca_com_heap.append(tempo_total_com_heap)

    # Plotando os resultados da busca
    plotar_resultados_busca(tamanhos_dados, tempos_busca_sem_heap, tempos_busca_com_heap)

if __name__ == "__main__":
    main()
