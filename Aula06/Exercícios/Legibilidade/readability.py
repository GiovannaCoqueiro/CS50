def main():
    sentence = input("Texto: ")
    letras = 0
    palavras = 1
    frases = 0

    # retorna o número de letras na sentença
    for char in sentence:
        if char.isalpha():
            letras += 1

    # retorna o número de palavras na sentença
    for char in sentence:
        if char.isspace():
            palavras += 1

    # retorna o número de frases na sentença
    for char in sentence:
        if char == '!' or char == '?' or char =='.':
            frases += 1

    # calcula a média de letras e frases a cada 100 palavras
    # e a formula de Coleman-Liau
    medlet = (letras * 100) / palavras
    medfra = (frases * 100) / palavras
    cl = (0.0588 * medlet) - (0.296 * medfra) - 15.8

    if cl < 1:
        print("Before Grade 1")
    elif cl > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(cl)}")

main()