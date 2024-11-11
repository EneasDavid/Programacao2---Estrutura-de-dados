import heapq  # Biblioteca que fornece a implementação de heaps (filas de prioridade)
import time  # Para medir o tempo de execução
import numpy as np  # Biblioteca para manipulação de arrays e geração de dados aleatórios
import matplotlib.pyplot as plt  # Biblioteca para plotagem de gráficos

# Função para ordenação sem heap (usando o método sort do Python)
def ordenar_sem_heap(dados):
    return sorted(dados)

# Função para ordenação utilizando heap
def ordenar_com_heap(dados):
    heap = []
    for item in dados:
        heapq.heappush(heap, item)
    return [heapq.heappop(heap) for _ in range(len(heap))]

# Função para medir o tempo de busca em uma lista não ordenada
def busca_nao_ordenada(lista, valor):
    inicio = time.time()
    _ = valor in lista  
        # Busca simples cxom 'in' para lista não ordenada, 
        # e o "_" como nome da variavel é porque é 
        # dispensavel o retorno, queremos apenas o tempo qeu leva
    return time.time() - inicio

# Função para medir o tempo de busca em uma lista ordenada (busca binária)
def busca_ordenada(lista, valor):
    inicio = time.time()
    esquerda, direita = 0, len(lista) - 1
    while esquerda <= direita:
        meio = (esquerda + direita) // 2 # "//" é a divisão inteira, no caso divide e arredonda o valor pro inteiro mais proximo
        if lista[meio] == valor:
            break
        elif lista[meio] < valor:
            esquerda = meio + 1
        else:
            direita = meio - 1
    return time.time() - inicio

# Função para plotar os resultados do benchmark de busca
def plotar_resultados_busca(tamanhos, tempos_nao_ordenado, tempos_ordenado):
    plt.figure(figsize=(12, 6))
    plt.plot(tamanhos, tempos_nao_ordenado, label='Busca em Lista de prioridade')
    plt.plot(tamanhos, tempos_ordenado, label='Busca em Lista de prioridade com Heap')
    plt.xlabel('Tamanho da Lista')
    plt.ylabel('Tempo de Execução (segundos)')
    plt.title('Comparação: Busca em Lista Não Ordenada vs Lista Ordenada')
    plt.legend()
    plt.show()

# Função principal
def main():
    # Lista de tamanhos de dados a serem testados
    tamanhos_dados = [10000, 20000, 30000, 40000, 50000]
    
    # Agora medindo o tempo de busca
    tempos_busca_nao_ordenada = []
    tempos_busca_ordenada = []
    #for(int i = 0; i < tamanhos_dados.size(); i++) {  # Código em C
    #   int tamanho = tamanhos_dados[i];
    # }
    for tamanho in tamanhos_dados:
        # Gerando dados aleatórios
        dados = np.random.randint(1, tamanho, tamanho)
        valores_procurados = np.random.randint(1, tamanho, 100)  # 100 valores a serem procurados

        # Medindo o tempo de busca em lista não ordenada
        tempo_total_nao_ordenado = 0
        for valor in valores_procurados:
            tempo_total_nao_ordenado += busca_nao_ordenada(dados, valor)
        tempos_busca_nao_ordenada.append(tempo_total_nao_ordenado)

        # Medindo o tempo de busca em lista ordenada
        dados_ordenados = sorted(dados)
        tempo_total_ordenado = 0
        for valor in valores_procurados:
            tempo_total_ordenado += busca_ordenada(dados_ordenados, valor)
        tempos_busca_ordenada.append(tempo_total_ordenado)

    # Plotando os resultados da busca
    plotar_resultados_busca(tamanhos_dados, tempos_busca_nao_ordenada, tempos_busca_ordenada)

if __name__ == "__main__":
    main()