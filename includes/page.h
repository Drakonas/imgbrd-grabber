#ifndef PAGE_H
#define PAGE_H

#include <QMap>
#include <QNetworkReply>
#include <QSslError>
#include "tag.h"
#include "image.h"
#include "functions.h"



class Image;
class Site;

class Page : public QObject
{
	Q_OBJECT

	public:
		explicit Page(Site *site, QMap<QString,Site*> *sites, QStringList tags = QStringList(), int page = 1, int limit = 25, QStringList postFiltering = QStringList(), bool smart = false, QObject *parent = 0, int pool = 0, int lastPage = 0, int lastPageMinId = 0, int lastPageMaxId = 0);
		~Page();
		void			setLastPage(Page *page);
		void			load(bool rateLimit = false);
		void			loadTags();
		QUrl			parseUrl(QString url, int pid, int p, QString t, QString pseudo, QString password);
		void			fallback(bool load = true);
		QList<Image*>	images();
		Site			*site();
		int				imagesCount(bool guess = true);
		int				pagesCount(bool guess = true);
		QUrl			url();
		QString			source();
		QString			website();
		QString			wiki();
		QList<Tag>		tags();
		QStringList		search();
		QStringList		errors();
		int				imagesPerPage();
		int				highLimit();
		int				page();
		int				minId();
		int				maxId();
		void			setUrl(QUrl url);
		QUrl			nextPage();
		QUrl			prevPage();

	public slots:
		void parse();
		void parseTags();
		void abort();
		void abortTags();
		void clear();

	signals:
		void finishedLoading(Page*);
		void failedLoading(Page*);
		void finishedLoadingTags(Page*);

	protected:
		void parseImage(QMap<QString,QString> data, int position);

	private:
		Site			*m_site;
		QString			m_format, m_website, m_source, m_wiki, m_originalUrl;
		QStringList		m_postFiltering, m_search, m_errors;
		QUrl			m_url, m_urlRegex, m_urlNextPage, m_urlPrevPage;
		QList<Image*>	m_images;
		int				m_imagesCount, m_pagesCount, m_imagesPerPage, m_currentUrl, m_page, m_blim, m_currentSource, m_pool, m_lastPage, m_lastPageMinId, m_lastPageMaxId;
		QList<Tag>		m_tags;
		QNetworkReply	*m_reply, *m_replyTags;
		bool			m_replyExists, m_replyTagsExists, m_smart;
};

#endif // PAGE_H
