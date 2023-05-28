# Задача об остовном дереве минимальной степени

## $\bf{NP}$-полнота
Докажем, что проверка существования остовного дерева максимальной степени не более $k$ (далее $\textsf{MDST}(k)$) является $\bf{NP}$-полной для любого фиксированного $k \ge 2$.

### $\bf{NP}$-трудность.
* Сведём $\bf{NP}$-полную задачу $\textsf{UHAMPATH}(G, s, t)$ о нахождении гамильтонова пути из $s$ в $t$ в неориентированном графе $G$ к задаче $\textsf{MDST}(2)$. Добавим в граф $G$ две вершины $a$, $b$, и проведём рёбра $(a,s)$ и $(b, t)$, получим граф $G'$. 
* Рассмотрим решение задачи $\textsf{MDST}(G', 2)$, это остовное дерево, степень каждой вершины в этом дереве не превосходит 2, а значит это путь между какими-то двумя вершинами, проходящий по всем вершинам графа $G'$. 
* Благодаря свойствам графа $G'$ этот путь выглядит как $a \rightarrow s \rightarrow \dots \rightarrow t \rightarrow b$. Откинув вершины $a$ и $b$, мы получим гамильтонов путь в графе $G$. Таким образом, мы построили биекцию между множествами гамильтоновых путей из s в t в графе $G$ и множеством остовных деревьев в графе $G'$, максимальная степень вершины в каждом не превосходит 2, а значит $\textsf{UHAMPATH} \le_p \textsf{MDST}(2) \Rightarrow \textsf{MDST}(2) \in \textbf{NPH}$.
* Теперь можем свести $\textsf{MDST}(2)$ к $\textsf{MDST}(k)$: для каждой вершины $v$ графа $G'$ добавим $k-2$ вершин и соединим рёбрами все эти вершины с вершиной $v$, получим граф $G''$. Таким образом, построили биекцию между $\textsf{MDST}(2)(G')$ и $\textsf{MDST}(k)(G'')$, а значит $\textsf{MDST}(2) \le_p \textsf{MDST}(k)$.

### Принадлежность к классу $\bf{NP}$
* Сведение $\textsf{MDST}(k)$ к $\bf{NP}$-полной задаче $\sf{CP}$ (a.k.a. Constraint Programming) и последующее решение [реализовано](tests/checks/optimal.cpp) с использование $\sf{CP}$-solver'а из библиотеки [OR-Tools](https://developers.google.com/optimization).
* Пусть граф $G=(V,E)$, $|V|=n$, $|E|=m$. Из задачи $\textsf{MDST}(k)(G)$ получим задачу $\sf{CP}$ с $n \cdot k(k-1) + m\cdot 2k$ булевых переменных. На эти переменные наложим следующие ограничения:
    1. [CircuitConstraint](https://github.com/google/or-tools/blob/82750ac12f1ee5354e1c7869894d9af3508778f2/ortools/sat/cp_model.h#LL858C21-L858C41) сопоставляет каждую переменную некоторому ориентированному ребру в графе $G^*$ с $n \cdot k$ вершин и накладывает ограничение, что выбранные рёбра, т.е. рёбра, переменная сопоставленная которому принимает значение $True$, образуют ориентированный гамильтонов цикл. Граф $G^*$, получен из графа $G$ следующим образом:
        * Каждую вершину $v$ исходного графа $G$ заменим на полный граф размера $k$. Эти вершины пронумеруем от $v_1$ до $v_k$. Отсюда получаем $n \cdot k$ вершин и $n \cdot k(k-1)$ ориентированных ребёр.
        * Каждое ребро $(u,v)$ исходного графа $G$ соответствуют $2k$ ориентированным рёбрам в графе $G^*$. Это рёбра $(u_i, v_i)$, $(v_i, u_i)$ для $i$ от $1$ до $k$.
    2. Пусть $E_{u,v}$ это множество булевых переменных, которые сопоставлены ориентированных рёбрам $(u_i, v_i)$, $i$ от $1$ до $k$, графа $G^*$. Тогда добавим ограничение, что для всех рёбер (u,v) графа $G$, значение $True$ может принимать не больше одной переменной среди $E_{u,v}$ и не больше одной среди $E_{v,u}$. А также $\bigvee_{x \in E_{u,v}} x = \bigvee_{x \in E_{v,u}} x$.
* **Утверждение**: в графе $G$ существует остовное дерево, максимальная степень вершины в котором не превосходит $k$ $\Leftrightarrow$ существует решение поставленной задачи $\sf{CP}$.
* $\Leftarrow:$ Пусть есть решение задачи $\sf{CP}$, значит существует ориентированный гамильтонов цикл в графе $G^*$, удовлетворяющий ещё некоторым ограничениям (2). Построим по нему некоторый подграф $G'$ графа $G$ следующим образом: если между полными подграфами, соответствующими вершинам $u$ и $v$ есть ребро, то это ребро графа $G'$.
    * В первую очередь ребро $(u, v)$ есть в графе $G$, в силу построения графа $G^*$.
    * Корректность обеспечивается ограничениями (2): если есть ребро между подграфами $u$ и $v$ в гамильтоновом цикле, то других ребёр $u \rightarrow v$ в цикле нет и существует ещё ровно одно ребро $v \rightarrow u$ в цикле.
    * Рёбра цикла делятся на рёбра между полными подграфами и на рёбра внутри одного полного подграфа. Из этого наблюдения можно сделать вывод, что граф $G'$ связен, поскольку мы можем добавлять в него рёбра в порядке обхода цикла и смотреть к какому подграфу принадлежит текущая вершина.
    * Так как цикл гамильтонов, то он посетил все вершины графа $G^*$ ровно по одному разу, значит он побывал в каждом полном подграфе, значит в графе $G'$ присутствуют все вершины графа $G$. 
    * Рассмотрим один полный подграф для какой-то вершины $v$. Гамильтонов цикл входит в это подграф и выходит из него не более $k$ раз, потому что размер подграфа $k$ и через каждую вершину цикл может пройти не более одного раза. Значит степень вершины $v$ в графе $G'$ тоже не больше $k$.
* В построенном графе $G'$ могут быть циклы. Удалив некоторые рёбра, так чтобы осталось остовное дерево, максимальная степень вершины в графе может только уменьшиться, а значит полученное дерево удовлетворяет нашим условиям.
* $\Rightarrow:$ Построим гамильтонов цикл в графе $G^*$ следующим алгоритмом. Запустим обратный обход остовного дерева в графе $G$. Пусть мы пришли в вершину $u$, последняя вершина в цикле это $u_i$. Пусть следующим шагом необходимо пройти по ребру $(u,v)$. Смотрим, встречается ли в цикле вершина $v_i$, если да, то ищем $j$ такой что вершины $u_j$ и $v_j$ непосещены, добавляем в цикл $u_j$, $v_j$, переходим в вершину $v$. Если в обходе дерева это последний раз, когда была посещена вершина $u$, то добавляем в цикл все вершины $u_i$, которые до этого не были посещены.
    * Так как степень каждой вершины в остовном дереве не больше $k$, то в нашем обходе в каждую вершину мы зайдём не больше $k$ раз, и выйдем соответственно столько же. В силу способа обхода, ограничение 2 будет выполнено.
    * Как выбирать $j$? Пусть когда мы зашли в первый раз в полный подграф, запомним и зафиксируем вершину, $j$ через которую нам нужно будет выйти. Дальше зафиксируем перестановку индексов, которая начинается с $i$ и заканчивается $j$. Далее при переходе в следующую вершину в остовном дереве, скажем, что мы должны вернуться через следующую вершину в перестановке. Аналогично по индукциию в следующем подграфе сможем выбрать порядок вершин в котором обходить, так чтобы вернуться через нужную вершину и сможем обойти всё поддерево и выйти через вершину $j$.
    * Цикл пройдёт через каждую вершину графа $G^*$, т.к. перед последним выходом из полного подграфа мы посетили все непосёщенные вершины полного подграфа.
* Таким образом, из утверждения следует, что $\textsf{MDST}(k) \in \textbf{NP}$, а следовательно $\textsf{MDST}(k) \in \textbf{NPC}$.
---
## Полиномиальный алгоритм приближённого решения
Пусть минимально возможная степень остовного дерева равна $\Delta$. [Алгоритм](src/spanning_tree.cpp) находит остовное дерево степени $\Delta$ или $\Delta + 1$ за полиномиальное время.
### Описание алгоритма
* Для начала алгоритмом Краскала найдём какое-нибудь остовное дерево (метод `BuildTree`), использует структуру данных [Disjoint Set Union](src/dsu.cpp).
* Далее алгоритм работает поэтапно (метод `ApproximateMinimumDegree`).
* Пусть $k$ это максимальная степень среди вершин текущего остовного дерева (в коде это `max_degree`). На каждом этапе алгоритм пытается уменьшить количество вершин степени $k$. Для этого рассматривается множества $S_k$ и $S_{k-1}$ вершин степени $k$ и $k-1$ соответственно. 
* В начале фазы (метод `DivideIntoComponents`), все вершины, кроме $S_k \cup S_{k-1}$ помечаются как *хорошие* (в коде `marks[v] = true`), а соответсвенно вершины степени хотя бы $k-1$ как *плохие* (`marks[v] = false`). 
* Далее рассматривается лес $F$ деревьев образованных удалением вершин $S_k \cup S_{k-1}$ (в коде лес хранится неявно с помощью `DSU`).
* Далее ищем рёбра (метод `FindEdge`) в исходном графе $G$, которые соединяют две *хорошие* вершины из разных деревьев леса $F$. 
* Если такого ребра нет, то алгоритм останавливается и возвращает найденный ответ. Об оптимальности найденного результата говорит теорема 5.1.
* **Теорема 5.1**: Пусть $T$ это какое-то остовное дерево графа $G$, максимальная степень вершины в котором равна $k$. Пусть $\Delta$ минимально возможная степень остовного дерева в графе $G$. Пусть $S$ это множество вершин дерева $T$ степени $k$, а $B$ это произвольное подмножество вершин $T$ степени $k-1$. Пусть лес $F$ образован удаление вершин $S \cup B$ из дерева $T$. Предположим, что граф $G$ удовлетворяет условию, что в нём нет рёбер соединяющие разные деревья леса $F$. Тогда $k \le \Delta+1$ 
* Если ребро нашлось, то алгоритм пытается сделать улучшение (метод `TryToImprove`) смотрит на цикл (метод `FindCycle`), который бы образовался в остовном дереве при добавлении этого ребра к дереву. 
* Далее смотрим на вершины в этом цикле. Если нашлась вершина степени $k$, то *пропагандируем* наше улучшение (метод `Propagate`). Иначе, нашлась хотя бы одна вершина степени $k-1$ (иначе рассматриваемое ребро не соединяло бы две вершины из разных деревьев леса $F$). Тогда запомним, что мы можем сделать каждую из этих вершин степени $k-1$ *неблокирующей* с помощью найденного ребра и отметим теперь эту вершину как *хорошую*, а также добавим эти вершины в лес $F$ и объединим деревья из найденного цикла в одно дерево и попытаемся ещё раз найти ребро. 
* **Определение 5.1**: Пусть дано ребро $(u,v)\notin T$ графа $G$, пусть вершина $w$ это некоторая вершина из цикла образованного добавлением ребра $(u,v)$ к остовному дереву $T$. Если $deg(u) \ge k-1$, то будем говорить, что вершина $u$ *блокирует* вершину $w$ относительно улучшения с помощью ребра $(u,v)$. Соответственно, если ни вершина $u$, ни вершина $v$ *неблокирующие* для вершины $w$, то степень вершины $w$ в дереве $T$ может быть уменьшена с помощью *шага по локальному улучшению*, то есть добавить в остовное дерево $T$ ребро $(u,v)$ и убрать одно из прилежащих рёбер из цикла с концом в $w$ не совпадающих с $(u,v)$.
* Улучшение остовного дерева делаются с помощью операции *пропагандирования*, которая рекурсивно выполняет *шаги по локальному улучшению*. Возможность осуществить эти локальные улучшения рекурсивно следует из леммы 5.1.
* **Лемма 5.1**: любая вершина $u$ помеченная как *хорошая*, может быть сделана *неблокирующей* в пределах поддерева образованного *хорошими* вершинами. Из данной леммы следует, что последующие локальные улучшения не будут пересекаться с предыдущими, потому что из леммы предыдущие улучшения могут быть сделаны в пределан поддерева *хороших* вершин, а последующие улучшения всегда используют рёбра, которые соединяют вершины из разных *хороших* деревьев. 

### Асимптотический анализ алгоритма
* Для начала оценим количество этапов. Каждый этап уменьшает количество вершин степени $k$ на один. В дереве с $n$ вершинами, вершин степени $k$ не больше чем $O(\frac{n}{k})$. Соответственно этапов, в которых максимальная степень вершины равна $k$ тоже $O(\frac{n}{k})$. Суммируя гармонический ряд получаем асимптотическую оценку количества этапов в $O(n \log n)$. 
* Каждый этап состоит из не более чем $n$ попыток улучшения остовного дерева, каждая попытка выполняется за $O(m \alpha(m, n))$
* Итоговая асимптотика алгоритма $O(n^2m\log n \cdot \alpha(m,n))$.