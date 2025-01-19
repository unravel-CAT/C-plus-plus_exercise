#ifndef STYLE_H
#define STYLE_H

class CPPStyle {
public:
    CPPStyle();
    CPPStyle(int a);
    ~CPPStyle();
    void setMember();
    int member();
private:
    int m_var;        // 普通成员变量
    static int s_var; // 静态成员变量
};
#endif // STYLE_H