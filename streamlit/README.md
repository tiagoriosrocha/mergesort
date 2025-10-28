# 📊 Análise de Algoritmos Híbridos com Streamlit

Este projeto apresenta uma **análise visual e interativa** de algoritmos híbridos baseados no **Merge Sort**, comparando variações que utilizam **Bubble Sort** e **Insertion Sort** como casos base.

---

## 🚀 Estrutura do Projeto

```
📁 streamlit/
 ├── app.py
 ├── merge4_final.c
 ├── merge5_final.c
 ├── merge-bubble-summary_results.csv
 ├── merge-insertion-summary_results.csv
 ├── merge-bubble-raw_times.csv
 ├── merge-insertion-raw_times.csv
 ├── melhores_resultados_merge_hibridos.csv
 ├── merge.png
 ├── bubble.png
 ├── insertion.png
 └── merge_bubble_threshold_6.png
```

---

## 🧠 Sobre o Projeto

Este aplicativo em Streamlit foi desenvolvido para a disciplina **CMP625 - Algorithms** do **Programa de Pós-Graduação em Computação da UFRGS**.

Ele permite explorar:

- O comportamento dos algoritmos híbridos Merge+Insertion e Merge+Bubble.
- A comparação com o Merge Sort puro.
- A relação entre os tempos reais e as curvas teóricas de complexidade.
- A análise do *threshold ideal* para cada abordagem.

---

## ▶️ Como Executar Localmente

### 1️⃣ Instale as dependências
```bash
pip install streamlit pandas numpy altair
```

### 2️⃣ Vá até a pasta principal e rode o app
```bash
cd streamlit
streamlit run app.py
```

O aplicativo será aberto automaticamente em seu navegador no endereço:
```
http://localhost:8501
```

---

## ☁️ Como Publicar Gratuitamente

Você pode publicar **gratuitamente** seu app usando o [Streamlit Community Cloud](https://share.streamlit.io):

1. Crie um repositório no GitHub (por exemplo, `algoritmos-hibridos-streamlit`).
2. Envie todos os arquivos dentro da pasta `streamlit/` para o repositório.
3. Acesse [share.streamlit.io](https://share.streamlit.io).
4. Conecte sua conta GitHub e escolha o repositório.
5. Defina o caminho do arquivo principal como:
   ```
   streamlit/app.py
   ```
6. Clique em **Deploy** e aguarde a publicação.

---

## 👨‍💻 Autor

**Tiago Rios da Rocha**  
Universidade Federal do Rio Grande do Sul (UFRGS)  
Disciplina: CMP625 - Algorithms  
Professor: Nicolas Maillard

---

## 📜 Licença

Este projeto é de uso acadêmico e livre para consulta e estudo.
