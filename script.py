import subprocess

# Função para rodar o programa em C++ com argumento string
def executar_programa_cpp(argumento):
    resultado = subprocess.run(['./tsp', argumento], 
                               capture_output=True, text=True)
    
    # Captura a saída e o código de retorno do programa
    saida = resultado.stdout
    codigo_retorno = resultado.returncode
    
    # Verifica se a execução foi bem-sucedida
    if codigo_retorno == 0:
        print(f"Saída do programa C++ com argumento '{argumento}':\n{saida}")
    else:
        print(f"Ocorreu um erro com argumento '{argumento}'. Código de retorno: {codigo_retorno}")
    
    return saida

# Função para executar o programa várias vezes com diferentes argumentos (strings)
def executar_varios(argumentos):
    for argumento in argumentos:
        executar_programa_cpp(argumento)

# Exemplo de uso
if __name__ == "__main__":
    # Lista de argumentos strings a serem passados ao programa C++
    argumentos = ["./instances/gr21.tsp", "./instances/gr24.tsp"]  # Substitua pelos seus valores desejados
    
    # Chama a função para executar o programa várias vezes
    executar_varios(argumentos)
