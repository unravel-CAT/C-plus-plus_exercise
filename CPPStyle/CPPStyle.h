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
    int m_var;        // ��ͨ��Ա����
    static int s_var; // ��̬��Ա����
};
#endif // STYLE_H