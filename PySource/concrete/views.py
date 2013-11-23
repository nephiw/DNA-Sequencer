from tkinter.constants import *
from tkinter import Tk, Text, StringVar
from tkinter import ttk

##
# The top of the view tree, the \ref GraphicalUserInterface subclasses Tk and provides the top level window
# for the UI.  All that is done here is layout, which is handled in the constructor, this view is mediated
# by \ref MainWindowMediator.
#
# @see concrete.views.MainTabInterface
# @see concrete.mediators.MainWindowMediator
##
class GraphicalUserInterface( Tk ):
    submitButton = None
    mainInterface = None
    progressIndicator = None
    statusLabel = None

    def __init__( self ):
        Tk.__init__( self )
        
        self.title( 'Multiple Sequence Aligner' )
        self.rowconfigure( 0, weight=1 )
        self.columnconfigure( 0, weight=1 )
        self.minsize(300,275)

        # Should probably add a frame here to make the padding look better.

        self.mainInterface = MainTabInterface( self )
        self.mainInterface.grid( column=0, row=0, columnspan=2, sticky=( N, W, E, S ) )

        #TODO when the UI is a separate thread, add this back.  Then fix statusLabel.
        self.progressIndicator = ttk.Progressbar( self, mode='indeterminate' )
        #self.progressIndicator.grid( column=0, columnspan=2, row=1, sticky=W )

        self.statusLabel = ttk.Label( self, pad=5 )
        self.statusLabel.grid( column=0, columnspan=2, row=1, sticky=W )

        self.submitButton = ttk.Button( self, text='Start' )
        self.submitButton.grid( column=1, row=1, sticky=E )

##
# \ref MainTabInterface subclasses ttk.Notebook and lays out the tabs and contains references to each of the tab's
# view classes. This view is mediated, along with \ref GraphicalUserInterface, by \ref MainWindowMediator.  All of the
# layout is handled in the constructor.
#
# @see concrete.views.GraphicalUserInterface
# @see concrete.mediators.MainWindowMediator
##
class MainTabInterface( ttk.Notebook ):
    dataSelectTab = None
    pairwiseSequenceTab = None
    multiSequenceTab = None
    resultsTab = None

    def __init__( self, parent ):
        ttk.Notebook.__init__( self, parent )

        self.dataSelectTab = DataSelectorInterface( self )
        self.pairwiseSequenceTab = PairwiseInterface( self )
        self.resultsTab = ResultsInterface( self )
        
        self.add( self.dataSelectTab, text='Input' )
        self.add( self.pairwiseSequenceTab, text='Settings' )
        self.add( self.resultsTab, text='Results' )

##
# \ref DataSelectorInterface subclasses ttk.Frame and lays out the data input interface. This view is mediated
# by \ref DataSelectorMediator.  All layout is handled in the constructor.
#
# @see concrete.mediators.DataSelectorMediator
##
class DataSelectorInterface( ttk.Frame ) :
    oneSequenceEntry = None
    twoSequenceEntry = None
    fileEntry = None
    fileBrowseButton = None

    def __init__( self, parent ):
        ttk.Frame.__init__( self, parent )
        self.config( padding='5 5 5 5' )
        self.columnconfigure( 1, weight=1, minsize=200 )

        ttk.Label( self, text='First Sequence').grid( column=1, row=1, columnspan=2, sticky=W )
        self.oneSequenceEntry = Text( self, height=4 )
        self.oneSequenceEntry.grid( column=1, row=2, columnspan=2, sticky=( E, W ) )

        ttk.Label( self, text='Second Sequence').grid( column=1, row=3, columnspan=2, sticky=W )
        self.twoSequenceEntry = Text( self, height=4 )
        self.twoSequenceEntry.grid( column=1, row=4, columnspan=2, sticky=( E, W ) )

        ttk.Label( self, text='File to Load').grid( column=1, row=5, columnspan=2, sticky=W )
        self.fileEntry = ttk.Entry( self )
        self.fileEntry.grid( column=1, row=6, sticky=( E, W ) )

        self.fileBrowseButton = ttk.Button( self, text='Browse' )
        self.fileBrowseButton.grid( column=2, row=6, sticky=W )

##
# \ref PairwiseInterface subclasses ttk.Frame and lays out the settings interface. This view is mediated
# by \ref PairwiseSequenceMediator.  All layout is handled in the constructor.
#
# @see concrete.mediators.PairwiseSequenceMediator
##
class PairwiseInterface( ttk.Frame ) :
    analysisComboBox = None
    openGapEntry = None
    openGapLabel = None
    extendGapEntry = None
    extendGapLabel = None
    gapPenaltyEntry = None
    gapPenaltyLabel = None
    matrixFileEntry = None
    matrixBrowseButton = None
    matrixComboBox = None
    showMatrixInGuiCB = None

    def __init__( self, parent ) :
        ttk.Frame.__init__( self, parent )
        self.config( padding='5 5 5 5' )
        self.columnconfigure( 1, weight=1, minsize=200 )

        self.useForester = StringVar()
        txt = 'Open with Archaeopteryx when complete'
        self.showMatrixInGuiCB = ttk.Checkbutton( self, text=txt, variable=self.useForester )
        self.showMatrixInGuiCB.grid( column=1, row=0, columnspan=2, sticky=W )

        ttk.Label( self, text='Substitution Matrix').grid( column=1, row=1, sticky=W )
        self.matrixComboBox = ttk.Combobox( self )
        self.matrixComboBox.grid( column=1, row=2, columnspan=2, sticky=( E, W ) )
        self.matrixFileEntry = ttk.Entry( self )
        self.matrixFileEntry.grid( column=1, row=3, sticky=( E, W ) )
        self.matrixBrowseButton = ttk.Button( self, text='Browse' )
        self.matrixBrowseButton.grid( column=2, row=3, sticky=E )

        ttk.Label( self, text='Gap Analysis Algorithm').grid( column=1, row=4, sticky=W )
        self.analysisComboBox = ttk.Combobox( self )
        self.analysisComboBox.grid( column=1, row=5, columnspan=2, sticky=( E, W ) )

        self.gapPenaltyLabel = ttk.Label( self, text='Gap Penalty')
        self.gapPenaltyLabel.grid( column=1, row=6, sticky=W )
        self.gapPenaltyEntry = ttk.Entry( self )
        self.gapPenaltyEntry.grid( column=1, row=7, columnspan=2, sticky=( E, W ) )

        self.openGapLabel = ttk.Label( self, text='Open Gap Penalty')
        self.openGapEntry = ttk.Entry( self )

        self.extendGapLabel = ttk.Label( self, text='Extend Gap Penalty')
        self.extendGapEntry = ttk.Entry( self )

##
# \ref ResultsInterface subclasses ttk.Frame and lays out the results interface. This view is mediated
# by \ref ResultMediator.  All layout is handled in the constructor.
#
# @see concrete.mediators.ResultMediator
##
class ResultsInterface( ttk.Frame ) :
    resultsArea = None

    def __init__( self, parent ) :
        ttk.Frame.__init__( self, parent )
        self.config( padding='5 5 5 5' )
        self.grid_columnconfigure(1, weight=1)
        self.grid_rowconfigure(1, weight=1)

        ttk.Label( self, text='Results' ).grid( column=1, row=1, sticky=W )
        self.resultsArea = Text( self )
        self.resultsArea.grid( column=1, row=1, sticky=( N, S, E, W ) )
        scrollbar = ttk.Scrollbar( self, orient=VERTICAL, command=self.resultsArea.yview )
        scrollbar.grid( column=2, row=1, sticky=( N, S ) )
        self.resultsArea['yscrollcommand'] = scrollbar.set
        self.resultsArea.insert('1.0','Your results will show here when complete.')
