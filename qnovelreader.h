#ifndef QNOVELREADER_H
#define QNOVELREADER_H

#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include <QFile>
#include <QList>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QCloseEvent>
#include <QTextStream>
#include <QProgressBar>
#include <QSystemTrayIcon>
#include <QStringListModel>

#include "qrule.h"
#include "qnovel.h"
#include "qchapter.h"
#include "qreadhistory.h"
#include "qsearchhistory.h"

#include "qthreadgetnovels.h"
#include "qthreadgetchapters.h"
#include "qthreadgetchapter.h"

namespace Ui {
class QNovelReader;
}

class QNovelReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit QNovelReader(QWidget *parent = 0);
    ~QNovelReader();

public slots:
    void getNovels();                           //��ȡС˵�б�
    void getChapters(QModelIndex);              //��ȡС˵�½�Ŀ¼
    void getChapter(QModelIndex);               //��ȡС˵�½�

    void updateProgress(qint64, qint64);        //���½�����
    void updateListView(const QList<QNovel>);   //����ListView��ʾС˵
    void updateListView(const QList<QChapter>); //����ListView��ʾ�½�Ŀ¼
    void updateTextArea(const QString, int);         //����TextArea��ʾ�½�����

    void setTextEditFont(QFont);                //����TextEdit������
    void setTextEditFontPointSize(QString);     //����TextEdit���ֺ�

    void refreshChapter();                      //ˢ���½�
    void getNextChapter();                      //��һ��
    void getPreviousChapter();                  //��һ��

    void downloadChapter();                     //���ص�ǰ�½�
    void downlaodNovel();                       //���ص�ǰС˵

    void changeHost(int);                       //�ı�С˵��Դ����

    void exitNovelReader();                     //�˳�����

    void onDoubleClickReadHistory(QModelIndex); //˫���Ķ���ʷ
    void updateListViewReadHistory(const QList<QChapter>);
    void updateTextAreaReadHistory(const QString, int i);

    void importReadHistoryFile();               //�����Ķ���ʷ�ļ�
    void exportReadHistoryFile();               //�����Ķ���ʷ�ļ�

    void deleteSelectedReadHistory();
    void deleteSelectedSearchHistory();

    void updateChapterContent(const QString, int);


private:
    //����
    Ui::QNovelReader *ui;                       //����

    int novelId;                                //��ǰ�Ķ���С˵id
    int chapterId;                              //��ǰ�Ķ����½�id
    int hostId;                                 //��ǰ����id

    QString ruleFileName;                       //�����ļ���
    QString readHistoryFileName;                //�Ķ���ʷ�ļ���
    QString searchHistoryFileName;              //������ʷ�ļ���

    QProgressBar *progressBar;                     //״̬��������
    QLabel *label;                              //״̬����ǩ

    QSystemTrayIcon *trayIcon;                  //������

    QList<QNovel> novelList;                    //С˵�б�
    QList<QRule> ruleList;                      //�����б�
    QList<QReadHistory> readHistoryList;        //�Ķ���ʷ�б�
    QList<QSearchHistory> searchHistoryList;    //������ʷ�б�

    //����
    void closeEvent(QCloseEvent *e);            //���ڹرգ����أ�

    void initHostComboBox();                    //��ʼ������ѡ���
    void initSystemTrayIcon();                  //��ʼ��������ͼ��

    void readRule();                            //��ȡ����
    void writeRule();                           //д�����

    void readReadHistory();                     //��ȡ�Ķ���ʷ
    void writeReadHistory();                    //д���Ķ���ʷ
    void updateReadHistory();                   //�����Ķ���ʷ
    void updateListViewReadHistory();           //�����Ķ���ʷ����
    int readHistoryIsContainsNovel(const QNovel &novel);

    void readSearchHistory();                   //��ȡ������ʷ
    void writeSearchHistory();                  //д��������ʷ
    void updateSearchHistory();                 //����������ʷ
    void updateListViewSearchHistory();         //����������ʷ����

    QString currentTime(const QString &format); //���ص�ǰʱ��
    int isContainsHost(const QString &host);
    QByteArray readFile(const QString &filename);
    bool writeFile(const QString &filename, const QByteArray &filecontent);

    void getNextFiveChapters();
};

#endif // QNOVELREADER_H
