#ifndef FAVORITESTAB_H
#define FAVORITESTAB_H

#include <QWidget>
#include <QMap>
#include "textedit.h"
#include "searchtab.h"
#include "page.h"
#include "mainwindow.h"



namespace Ui
{
	class favoritesTab;
	class mainWindow;
}



class mainWindow;

class favoritesTab : public searchTab
{
	Q_OBJECT

	public:
		explicit favoritesTab(int id, QMap<QString,Site*> *sites, QList<Favorite> favorites, mainWindow *parent);
		~favoritesTab();
		Ui::favoritesTab *ui;
		QList<bool> sources();
		QString tags();
		QString wiki();
		int imagesPerPage();
		int columns();
		QString postFilter();

	public slots:
		void updateCheckboxes();
		// Search
		void firstPage();
		void previousPage();
		void nextPage();
		void lastPage();
		// Zooms
		void setTags(QString);
		void webZoom(int);
		// Loading
		void load();
		void finishedLoading(Page*);
		void failedLoading(Page*);
		void postLoading(Page*);
		void finishedLoadingTags(Page*);
		void finishedLoadingPreview(Image*);
		// Batch
		void getPage();
		void getAll();
		void getSel();
		// Tag list
		void linkHovered(QString);
		void linkClicked(QString);
		void openInNewTab();
		void openInNewWindow();
		// History
		void historyBack();
		void historyNext();
		// Favorites
		void favoriteProperties(QString);
		void updateFavorites();
		void loadFavorite(QString);
		void checkFavorites();
		void loadNextFavorite();
		void favoritesBack();
		void setFavoriteViewed(QString);
		void viewed();
		// Others
		void optionsChanged();
		void closeEvent(QCloseEvent*);
		void toggleImage(int, bool);
		void addTabFavorite(QString);
		void setImagesPerPage(int);
		void setColumns(int);
		void setPostFilter(QString);

	signals:
		void batchAddGroup(QStringList);
		void batchAddUnique(QMap<QString,QString>);

	private:
		int								m_id;
		mainWindow						*m_parent;
		TextEdit						*m_postFiltering;
		QDateTime						m_loadFavorite;
		QList<Favorite>					m_favorites;
		QMap<QString,Page*>				m_pages;
		QList<Image*>					m_images;
		int								m_pagemax;
		QString							m_lastTags, m_wiki, m_currentTags;
		bool							m_sized, m_from_history, m_stop;
		int								m_page, m_history_cursor, m_currentFav;
		QList<QGridLayout*>				m_layouts;
		QList<QMap<QString,QString> >	m_history;
		QStringList						m_modifiers;
};

#endif // FAVORITESTAB_H
