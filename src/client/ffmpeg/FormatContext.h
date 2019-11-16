#ifndef MICROMACHINES_FORMATCONTEXT_H
#define MICROMACHINES_FORMATCONTEXT_H


class FormatContext {
private:
    AVFormatContext *pFormatCtx;
public:
    FormatContext();

    AVFormatContext* getContext() const;

    void dumpFormat(const std::string& filename);

    ~FormatContext();
};


#endif //MICROMACHINES_FORMATCONTEXT_H
