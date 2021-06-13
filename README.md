# 構文解析の注意点
- エラー出力で動作を追うこと
  - 一括でトグルできるやつ欲しい
- BNFは改善できる場合がある
- 簡単なものはパーサー書かなくてもいいよ
- 左再帰はループに変える
  - 終了条件に注意
- 基本的には変数総当たり
- 区間DPやメモ化再帰，しゃくとりもあり
  - 区間DPやメモ化再帰は演算子で区切りがち
- `getline(cin, s)`
- `s.erase(remove(s.begin(), s.end(), ' '), s.end())`
- `try-catch`で飛ばせると楽
  - `throw "xxx"` は `catch(const char*)` で受ける

# 構文解析全問レビュー
## AOJ 0109
### 概要
- 四則演算（括弧あり）
- 最後に`=`が付く（無視する）
- 結果は`int`に収まる
### BNF
```
<expr> ::= <term> | <expr>+<term> | <expr>-<term>
<term> ::= <fact> | <term>*<fact> | <term>/<fact>
<fact> ::= <numb> | (<expr>)
<numb> ::= [1-9] [0-9]*
```
左再帰をループに書き換えて
```
<expr> ::= <term> [ +<term> | -<term> ]*
<term> ::= <fact> [ *<fact> | /<fact> ]*
<fact> ::= <numb> | (<expr>)
<numb> ::= [1-9] [0-9]*
```

## AOJ 0264
### 概要
- 四則演算（括弧あり）
- mod
- 行読み込み
### BNF
0109といっしょ

## AOJ 1155
### 概要
- 三値論理
- 変数総当たり
### BNF
```
<formula> ::= 0 | 1 | 2 | P | Q | R |
              -<formula> |
              (<formula>*<formula>) | (<formula>+<formula>)
```

## AOJ 2401
### 概要
- ニ値論理，論理包含
- 変数総当たり
- 恒等式
### BNF
```
<formula> ::= T | F |
              a | b | c | d | e | f | g | h | i | j | k |
              - <formula> |
              (<formula>*<formula>) | (<formula>+<formula>) | (<formula>-><formula>)
```
`A -> B`はド・モルガンの法則から`-A ∨ B`になることに注意．

## AOJ 2883
### 概要
- ニ値論理，演算子が前
- 変数総当たり
### BNF
```
<Hash> ::= <Letter> | [<Op><Hash><Hash>]
<Op> ::= + | * | ^
<Letter> ::= a | b | c | d
```

## AOJ 1244
### 概要
- 原子量から分子量を求める
- 変数名不定
- パース途中で例外処理
### BNF
少し手を入れてマージンを作ると解きやすい
```
<Molecule> ::= <fact> [<fact>]*
<fact> ::= <Atom> [<Number>]? | (<Molecule>) <Number>
<Atom> ::= [A-Z] [a-z]?
<Number> ::= [1-9] [0-9]?
```

## AOJ 0110
### 概要
- 128bit
- 変数総当たり
- Leading 0 殺し
### BNF
```
<expr> ::= <numb> [ +<numb> ]*
<numb> ::= [ 1-9 | X ] [ 0-9 | X ]*
```

## AOJ 2584
### 概要
- 変数総当たり（のフリ）
- アルファベット
### BNF
```
<Cipher> ::= <String> [<String>]*
<String> ::= <Letter> | '['<Cipher>']'
<Letter> ::= ['+' | '-']* [A-Z | ?]
```

## AOJ 2255
### 概要
- 区間DP
  - $dp[l][r] := [l, r)$ による部分数式の解集合
  - `set`で管理するの異常
- 演算順序無視
- 括弧の深さに注意

## AOJ 2613
### 概要
- 演算子順序全探索
### BNF
```
<expr> ::= <term1>[op0<term1>]*
<term1> ::= <term2>[op1<term2>]*
<term2> ::= <fact>[op2<fact>]*
<fact> ::= <numb> | (<expr>)
<numb> ::= [0-9]+
```

## AOJ 2369
### 概要
- BNFを改造するタイプ
- 停止性に注意
### BNF
```
CAT ::= m[CAT]eCat
eCat ::= e[CAT]w
```

## AOJ 2435
### 概要
- 逆ポーランド記法
- 取りうる値を全てメモ
  - `set`で管理

## AOJ 2643
### 概要
- シミュレーション
- メモ化
  - 文字列の位置をメモするのがコツ
### BNF
```
<Program> := [<Sentence>]*
<Sentence> := [<Condition><Program>] | {<Condition><Program>} | <Move>
<Move> :=  ^ | v | < | >
<Condition> := [~] N | E | S | W | C | T
```

## AOJ 1282
### 概要
- 配列パース
- BNF が少ないので難しいところだけパーサを使う
### BNF
```
<expression> ::= <number> | <array_name> [ <expression> ]
<number> ::= 0 | [1-9] [0-9]*
<array_name> ::= [a-zA-Z]
```

## AOJ 1371
### 概要
- 暗号化
- 重複しないように割り当てたあと，それらについて構文解析
  - 未知の記号と解析が最後まで行かない場合は `throw`
- 等号の数および未割り当ての数え上げに注意
### BNF
```
<E> ::= <T> [ + <T> | − <T>]*
<T> ::= <F> [ ∗ <F> ]*
<F> ::= <N> | − <F> | ( <E> )
<N> ::= 0 | 1 [01]*
```

## AOJ 2570
### 概要
- 右括弧に関数呼び出しと右シフトの2つの意味がある
  - 先読みして一意に定める
- 右シフトのオーバーフローに注意
- 空白削除は `s.erase(remove(s.begin(), s.end(), ' '), s.end())`
### BNF
```
<expr> ::= <term> [ >> <term> ]*
<term> ::= <number> | S< <expr> >
<number> ::= 0 | [1-9][0-9]*
```

## AOJ 1012
### 概要
- 集合演算
- 演算子の優先順位を考える
### BNF
```
<expr> ::= <term> [ [uids] <term> ]*
<term> ::= c <name> | ( <expr> )
<name> ::= [A-E]
```

## AOJ 2740
### 概要
- 二分木の解析と復元
  - 復元は根から降りるときに結合していけば良い
### BNF
```
<tree> ::= ( <term> ) [ <number> ] ( <term> )
<term> ::= "" | <tree>
<number> ::= [0-9]+
```

[2018-G]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1630
[2017-E]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1620
[2015-C]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1602
[2013-C]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1188
[2012-F]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1184
[2011-B]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1173
[2008-C]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Prelim/1155
[aoj0109]: https://onlinejudge.u-aizu.ac.jp/challenges/search/volumes/0109
[asia2003-E]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/ICPC/Regional/1244
[jag2012-C]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Prelim/2401
[jag2018-C]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Prelim/2883
[aoj0264]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/PCK/Prelim/0264
[aoj0110]: https://onlinejudge.u-aizu.ac.jp/challenges/search/categories/0110
[jag2014-C]: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Prelim/2584?year=2014

### [（未）論理式圧縮機 &mdash; ICPC国内予選2017E][2017-E]
```
<E> ::= 0 | 1 | a | b | c | d |
        -<E> |
        (<E>^<E>) | (<E>*<E>)
```
```
0 ::= (0 * <E>) | (<E> * 0)
<E> ::= (1 * <E>) | (<E> * 1)
<E> ::= (0 ^ <E>) | (<E> ^ 0)
-<E> ::= (1 ^ <E>) | (<E> ^ 1)
```

### [数式探し &mdash; ICPC国内予選2018G][2018-G]
しゃくとり
でも1*1*…* 1がやばいのでそこはまとめる
あと
(1+2)* 3+3 で3になるのが4つなわけなくない？うそ．1+2と(1+2)は別物だったりして