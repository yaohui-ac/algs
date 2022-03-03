#include<bits/stdc++.h>
constexpr int N = 1e5 + 5; //串长

char s[N], p[N];
int  nxt[N];
//---关于字符串匹配算法的实现---//


// 定义1: Border如果字符串 S 的同长度的前缀和后缀完全相同，即 Prefix[i] = Suffix[i]
// 则称此前缀（后缀）为一个 Border

//定义2: 对于字符串 S 和正整数 p，如果有 S[i] = S[i − p]，对于 p < i ≤ |S| 成
//成立，则称 p 为字符串 S 的一个周期。
//特殊地，p = |S| 一定是 S 的周期

//定义3: 若字符串 S 的周期 p 满足 p | |S|，则称 p 为 S 的一个循环节

//性质 : p 是 S 的周期 ⇔ |S| − p 是 S 的 Border

//1. KMP //
//KMP就是利用前缀串的Border进行优化的
//定义next[i]表示字符串p长度为i的前缀子串最大Border (nxt数组)

/*求next数组*/
// 串S 的 Border 的 Border 也是 S 的 Border
//next[i] = Preffix[i] 的非平凡的最大 Border
//next[1] = 0

/*

next[i] = Prefix[i] 的非平凡的最大 Border
next[1] = 0
考虑 Prefix[i] 的所有（长度大于 1 的）Border，去掉最后一个字母，就
会变成 Prefix[i − 1] 的 Border。

*/
void get_next(const char* s) {
 //用kmp字符串匹配的时t候,为方便 下标从1开始
   memset(nxt, 0, sizeof nxt);
    int len = strlen(s + 1); //1才是起点
    for(int i = 2; i <= len; i++) {
        int j = nxt[i - 1];
        while(j && s[i] != s[j + 1])
            j = nxt[j];
        nxt[i] = j + (s[i] == s[j + 1]);
    }
}
void find_1(const char *p, const char *s) {
    //找p在s中出现的位置,0号位置都空住
    get_next(p);
    int n = strlen(p + 1);
    int m = strlen(s + 1);
    for(int i = 1, j = 0; i <= m; i++) {
        //j 代表匹配的长度
        while(j && s[i] != p[j + 1])
            j = nxt[j];
        if(s[i] == p[j + 1]) j++;
        if(j == n) {
            std:: cout << "idx: " << i - j + 1 << "\n";
            j = nxt[j];
        }    
    }
}
// ------- sunday算法------- //

// 也需要维护一些东西
// 从前向后匹配,失配时(假设下标i失配)检查对齐的后一个位置s[n + 1]
// 如果 s[n + 1] ∈ p,则将其这个位置对其到p串中 最后面的 等于s[n + 1]的字符的位置
// 如果不, 说明[i, n + 1]都不可能匹配(如果该字符没有在模式串中出现则直接跳过)
// 所以需要维护一张偏移表
// 最坏情况下时间复杂度为：O(nm)
// 平均时间复杂度：O(n)

std::unordered_map<char, int>shift; //假设这样维护偏移
void get_shift(const char* p) {
    int len = strlen(p + 1); //下标1开始存放
    for(int i = 1; i <= len; i++)
        shift[p[i]] = i; 
}
void find_2(const char* p ,const char * s) {
    // 找p在s中出现的位置,0号位置都空住
    shift.clear();
    get_shift(p);
    int n = strlen(p + 1);
    int m = strlen(s + 1);
    int i = 1, j = 0; // j为已经匹配的长度
    int idx;
    while(i <= m) {
        if(s[i] == p[j + 1]) {
            j++;
            if(j == n) { //匹配成功
                std:: cout << "idx: " << i - j + 1 << "\n";
                j = 0;
            }
            i++;
            continue;
        }
        idx = i - j + n; //末尾字符
        if(idx > m) break;
        int offset = shift[s[idx]];
        if(offset == 0) { //不被包含
            i = idx + 1;
            j = 0;
        }
        else {
            i = idx - offset + 1; //
            j = 0;
        }
    }
}

// ----- Horspool算法 -----//
// Horsepool算法是Boyer-Moore算法的简化版本，这也是一个空间换时间的典型例子。
// 算法把模式P和文本T的开头字符对齐，从模式的最后一个字符开始比较，如果尝试比较失败了，它把模式向后移。每次尝试过程中比较是从右到左的。
// 和sunday基本类似，但是是从后往前匹配的,失配位置不在模式串中则平移整个字符串。在模式串中则对齐
// 所以需要维护一张偏移表(可以直接拿sunday算法的表)
// 最坏情况下时间复杂度为：O(nm)
// 平均时间复杂度：O(n)
void find_3(const char* p ,const char* s) {
    shift.clear();
    get_shift(p);
    int n = strlen(p + 1);
    int m = strlen(s + 1);
    if(n > m) return;
    int i = 1, j = 0; // j为已经匹配的长度
    int idx = i + n - 1; //当前匹配的末尾
    while(idx <= m) {
        if(p[n - j] == s[idx - j]) {
            j++;
            if(j == n) {
                std::cout << "idx: " << idx - j + 1 << "\n";
                j = 0;
                idx += n;
            }
            continue;
        }
        int offset = shift[s[idx - j]]; //偏移位置
        idx = (idx - j) + n - offset;
        j = 0;

    }
    
}
// ------ Boyer-Moore算法 ------//
// 一般文本编辑器中的查找功能都是基于它实现的.
// 可以认为是horspool算法 + kmp算法的实现
// 当然kmp是最大前缀,BM算法要求 后缀
// horspool算法提供坏字符的启发方法
// kmp算法提高好后缀的启发方法(需要改改)
// 哪种方法,获得的移动位置大,就使用哪种启发
//O(N)
void get_suffix(const char* p) {
    memset(nxt, 0, sizeof nxt);
    int len = strlen(p + 1);
    
}
void find_4(const char* p ,const char* s) {
   

    
}



//-----Rabin-Karp算法-----//
// 实际上就是字符串哈希 + 前缀和. 且受到字符集大小的限制,而且有可能存在哈希冲突
// 只不过比平常的字符串哈希好一点,只算长度为m的子串
// Rabin-Karp算法的想法是为t每一个长度为m的子串求一个hash值，然后和s的hash值匹配 
// 如果匹配上了，再去匹配字符串本身。
// 正常情况下计算hash值的复杂度是o(m)， 所以整个算法依然是o(mn)。
// 但是如果设计较好的hash算法， 让每个子串的hash值通过它前一个子串的hash值快速算出来（因为他们毕竟有m-1个字符完全一样
// 这样平均复杂度就能降低到o(n)。一个最简单的hash函数即m个元素的和。在已知前一个字符串的hash值以及两个字符串的差异之后，可以快速求出后一个字符串的hash值。




void verify() {
    const char* s = "123123123";
    const char* p = "123";
    find_1(p, s);
    puts("-----");
    find_2(p, s);
    puts("-----");
    find_3(p, s);
}

int main () {
    verify();
}



