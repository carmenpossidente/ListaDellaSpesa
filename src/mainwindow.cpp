#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QMenu>
#include <QFont>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinQuantita->setMinimum(1);
    inizializzaCategorie();
    ui->listOggetti->setContextMenuPolicy(Qt::CustomContextMenu);

    // Connessioni
    connect(ui->listOggetti, &QListWidget::customContextMenuRequested,
            this, &MainWindow::mostraMenuContextuale);
    connect(ui->listOggetti, &QListWidget::itemChanged,
            this, &MainWindow::aggiornaStileOggetto);
    connect(ui->comboFiltroCategoria, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            this, &MainWindow::filtraPerCategoria);

    aggiornaTotale();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAggiungi_clicked()
{
    QString nome = ui->lineEditNome->text().trimmed();
    int quantita = ui->spinQuantita->value();
    QString categoria = ui->comboCategoria->currentText();

    if (nome.isEmpty()) {
        QMessageBox::warning(this, "Errore", "Inserisci un nome valido");
        return;
    }

    // Formato: "Nome (Categoria) xQuantità"
    QListWidgetItem* item = new QListWidgetItem(
            nome + " (" + categoria + ") x" + QString::number(quantita)
    );

    // Rendo l'oggetto checkable
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked);

    // Salvo i dati come UserRole per usarli dopo
    QVariantMap dati;
    dati["nome"] = nome;
    dati["categoria"] = categoria;
    dati["quantita"] = quantita;
    item->setData(Qt::UserRole, dati);

    ui->listOggetti->addItem(item);
    aggiornaTotale();

    // Reset dei campi
    ui->lineEditNome->clear();
    ui->spinQuantita->setValue(1);
    ui->comboCategoria->setCurrentIndex(0);
}

void MainWindow::mostraMenuContextuale(const QPoint &pos)
{
    QListWidgetItem *item = ui->listOggetti->itemAt(pos);
    if (!item) return;

    QMenu menu(this);
    QAction *rimuovi = menu.addAction("Rimuovi");

    QAction *azioneScelta = menu.exec(ui->listOggetti->mapToGlobal(pos));

    if (azioneScelta == rimuovi) {
        delete ui->listOggetti->takeItem(ui->listOggetti->row(item));
        aggiornaTotale();
    }
}

void MainWindow::aggiornaTotale()
{
    int totalePezzi = 0;
    int totaleOggetti = 0;

    for (int i = 0; i < ui->listOggetti->count(); ++i) {
        QListWidgetItem* item = ui->listOggetti->item(i);
        if (item->checkState() == Qt::Unchecked) {
            QVariantMap dati = item->data(Qt::UserRole).toMap();
            totalePezzi += dati["quantita"].toInt();
            totaleOggetti++;
        }
    }

    QString testo;
    if (totaleOggetti == 0) {
        testo = "📋 0 oggetti | 🛒 0 pezzi da acquistare";
    } else {
        testo = QString("📋 %1 oggetti | 🛒 %2 pezzi da acquistare")
                .arg(totaleOggetti)
                .arg(totalePezzi);
    }

    ui->labelTotale->setText(testo);
}

void MainWindow::inizializzaCategorie()
{
    QStringList categorie = { "Alimentari", "Casa", "Igiene", "Altro" };

    ui->comboCategoria->addItems(categorie);
    ui->comboFiltroCategoria->addItem("Tutte");
    ui->comboFiltroCategoria->addItems(categorie);
}

void MainWindow::aggiornaStileOggetto(QListWidgetItem* item)
{
    QFont font = item->font();
    if (item->checkState() == Qt::Checked) {
        font.setStrikeOut(true);
        item->setForeground(Qt::gray);
    } else {
        font.setStrikeOut(false);
        item->setForeground(Qt::black);
    }
    item->setFont(font);
    aggiornaTotale();
}

void MainWindow::filtraPerCategoria(const QString &categoriaSelezionata)
{
    for (int i = 0; i < ui->listOggetti->count(); ++i) {
        QListWidgetItem* item = ui->listOggetti->item(i);
        QVariantMap dati = item->data(Qt::UserRole).toMap();
        QString categoriaItem = dati["categoria"].toString();

        if (categoriaSelezionata == "Tutte" || categoriaSelezionata == categoriaItem) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}