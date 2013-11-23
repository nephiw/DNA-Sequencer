from tkinter.constants import *
from tkinter.messagebox import showinfo
from tkinter import filedialog

from comm import valueObjects
from comm.messages import Messages
import patterns.mediator

##
# Mediates \ref GraphicalUserInterface and \ref MainTabInterface.  Once initialized, \ref MainWindowMediator add the
# virtual event listeners for the submit button
#
# @see\ref patterns.mediator.Mediator
# @see\ref concrete.views.MainTabInterface
# @see\ref concrete.mediators.MainWindowMediator
##
class MainWindowMediator( patterns.mediator.Mediator ) :
    NAME = "MainWindowMediator"

    # TODO: Add the progress bar and progress text box mediation here.
    def __init__( self, viewComponent ) :
        super( ).__init__( MainWindowMediator.NAME, viewComponent )

    def listNotificationInterests( self ) :
        return [ Messages.SHOW_RESULTS, Messages.UPDATE_STATUS_TEXT ]

    def handleNotification( self, notification ) :
        if notification.getName( ) == Messages.SHOW_RESULTS :
            self.viewComponent.mainInterface.select( self.viewComponent.mainInterface.resultsTab )
            self.viewComponent.progressIndicator.stop()
        elif notification.getName( ) == Messages.UPDATE_STATUS_TEXT :
            self.viewComponent.statusLabel.config( text=notification.getBody() )

    def onRegister( self ) :
        self.viewComponent.submitButton.config( command=self.notifyStart )
        self.viewComponent.statusLabel.config( text='Application Started' )

    # Start mediator specific methods.
    def notifyStart( self ) :
        self.viewComponent.progressIndicator.start()
        self.sendNotification( Messages.START )


##
# \ref PairwiseInterface.  Once initialized, \ref PairwiseSequenceMediator configures the combo boxes and sets
# up virtual event listeners on the buttons.  When the application requests a state save, \ref PairwiseSequenceMediator
# creates a \ref PairwiseSelectorVO to store the sequencer's settings.
#
# @see\ref patterns.mediator.Mediator
# @see\ref concrete.views.PairwiseInterface
# @see\ref comm.valueObjects.PairwiseSelectorVO
##
class PairwiseSequenceMediator( patterns.mediator.Mediator ) :
    NAME = "PairwiseSequenceMediator"

    def __init__( self, viewComponent ) :
        super( ).__init__( PairwiseSequenceMediator.NAME, viewComponent )

    def listNotificationInterests( self ) :
        return [ Messages.STORE_CURRENT_STATE ]

    def handleNotification( self, notification ) :
        if notification.getName( ) == Messages.STORE_CURRENT_STATE :
            self.sendNotification( Messages.STORE_VIEW_STATE, self.createStateObject( ) )

    def onRegister( self ) :
        self.viewComponent.matrixBrowseButton.config( command=self.notifyFileBrowse )
        self.viewComponent.matrixComboBox[ 'values' ] = ( 'BLOSUM45', 'BLOSUM50', 'BLOSUM62', 'BLOSUM80', 'PAM30', 'PAM70' )

        self.viewComponent.matrixComboBox.state( [ 'readonly' ] )
        self.viewComponent.matrixComboBox.set( 'BLOSUM62' )
        self.viewComponent.analysisComboBox[ 'values' ] = ( 'Local', 'Global', 'Affine' )
        self.viewComponent.analysisComboBox.state( [ 'readonly' ] )
        self.viewComponent.analysisComboBox.set( 'Local' )
        self.viewComponent.analysisComboBox.bind( '<<ComboboxSelected>>', self.transformPage )
        self.viewComponent.showMatrixInGuiCB.config( onvalue='true', offvalue='false' )
        self.viewComponent.showMatrixInGuiCB.invoke()

    def createStateObject( self ) :
        psvo = valueObjects.PairwiseSelectorVO( )
        psvo.openGapValue = self.viewComponent.openGapEntry.get( )
        psvo.extendedGapValue = self.viewComponent.extendGapEntry.get( )
        psvo.gapPenaltyValue = self.viewComponent.gapPenaltyEntry.get( )
        psvo.matrixFileValue = self.viewComponent.matrixFileEntry.get( )
        psvo.matrixBoxValue = self.viewComponent.matrixComboBox.get( )
        psvo.analysisBoxValue = self.viewComponent.analysisComboBox.get( )
        psvo.useForester = ( 'true' == self.viewComponent.useForester.get( ) )
        return psvo

    def notifyFileBrowse( self ) :
        vo = valueObjects.FileReturnVO( )
        vo.msg = 'Choose a file to use as a substitution matrix'
        vo.entry = self.viewComponent.matrixFileEntry
        self.sendNotification( Messages.FIND_FILES, vo )

    # event is not used, it is required for the virtual event callback.
    #noinspection PyUnusedLocal
    def transformPage( self, event=None ) :
        val = self.viewComponent.analysisComboBox.get( )
        if val == 'Affine' :
            self.viewComponent.openGapLabel.grid( column=1, row=6, sticky=W )
            self.viewComponent.openGapEntry.grid( column=1, row=7, columnspan=2, sticky=( E, W ) )
            self.viewComponent.extendGapLabel.grid( column=1, row=8, sticky=W )
            self.viewComponent.extendGapEntry.grid( column=1, row=9, columnspan=2, sticky=( E, W ) )
            self.viewComponent.gapPenaltyLabel.grid_remove( )
            self.viewComponent.gapPenaltyEntry.grid_remove( )
        else :
            self.viewComponent.openGapEntry.grid_remove( )
            self.viewComponent.openGapLabel.grid_remove( )
            self.viewComponent.extendGapEntry.grid_remove( )
            self.viewComponent.extendGapLabel.grid_remove( )
            self.viewComponent.gapPenaltyLabel.grid( column=1, row=6, sticky=W )
            self.viewComponent.gapPenaltyEntry.grid( column=1, row=7, columnspan=2, sticky=( E, W ) )


##
# Mediates \ref DataSelectorInterface.  Once initialized, \ref DataSelectorMediator sets up virtual event listeners on
# the buttons.  When the application requests a state save, \ref PairwiseSequenceMediator
# creates a \ref DataSelectorVO to store the data objects that will be sequenced.
#
# @see\ref patterns.mediator.Mediator
# @see\ref concrete.views.DataSelectorInterface
# @see\ref comm.valueObjects.DataSelectorVO
##
class DataSelectorMediator( patterns.mediator.Mediator ) :
    NAME = "DataSelectorMediator"

    def __init__( self, viewComponent ) :
        super( ).__init__( DataSelectorMediator.NAME, viewComponent )

    def listNotificationInterests( self ) :
        return [ Messages.STORE_CURRENT_STATE ]

    def handleNotification( self, notification ) :
        if notification.getName( ) == Messages.STORE_CURRENT_STATE :
            self.sendNotification( Messages.STORE_VIEW_STATE, self.createStateObject( ) )

    def onRegister( self ) :
        # TODO If we are returning from a pause, we need to initialize the fields too.
        self.viewComponent.fileBrowseButton.config( command=self.notifyFileBrowse )

    def createStateObject( self ) :
        dsvo = valueObjects.DataSelectorVO( )
        dsvo.sequenceOne = self.viewComponent.oneSequenceEntry.get( 1.0, END )
        dsvo.sequenceOne = ''.join( dsvo.sequenceOne.split( ) )
        dsvo.sequenceTwo = self.viewComponent.twoSequenceEntry.get( 1.0, END )
        dsvo.sequenceTwo = ''.join( dsvo.sequenceTwo.split( ) )
        dsvo.filePath = self.viewComponent.fileEntry.get( )
        return dsvo

    def notifyFileBrowse( self ) :
        vo = valueObjects.FileReturnVO( )
        vo.msg = 'Choose a fasta data file'
        vo.entry = self.viewComponent.fileEntry
        self.sendNotification( Messages.FIND_FILES, vo )


##
# Mediates \ref ResultsInterface.  Once initialized, \ref ResultMediator sets up virtual event listeners on
# the buttons.  \ref ResultMediator does not save it's state because it's state can be created upon the states
# of the other value objects.  \ref ResultMediator does respond to the show result message, receiving a string
# to display on the screen.
#
# @see patterns.mediator.Mediator
# @see concrete.views.ResultsInterface
##
class ResultMediator( patterns.mediator.Mediator ) :
    NAME = "ResultMediator"
    firstRun = True

    def __init__( self, viewComponent ) :
        super( ).__init__( ResultMediator.NAME, viewComponent )

    def listNotificationInterests( self ) :
        return [ Messages.SHOW_RESULTS ]

    def handleNotification( self, notification ) :
        if notification.getName( ) == Messages.SHOW_RESULTS :
            if self.firstRun :
                self.viewComponent.resultsArea.delete( '1.0', END )
                self.firstRun = False
            results = notification.getBody( )
            self.viewComponent.resultsArea.insert( END, results )
            self.viewComponent.resultsArea.insert( END, '\n\n' )

    def onRegister( self ) :
        pass

##
# Mediates an instance of tkinter's show info box.  It is essentially an alert box.  When non-view elements want to
# display a message to the screen, a notification will be sent that will result in this mediator creating and
# displaying the message sent to it.  For more information in tkinter, visit this site: http://www.tkdocs.com/
#
# @see patterns.mediator.Mediator
##
class ShowInfoMediator( patterns.mediator.Mediator ) :
    NAME = "ShowInfoMediator"

    def __init__( self, viewComponent ) :
        super( ).__init__( ShowInfoMediator.NAME, viewComponent )

    def listNotificationInterests( self ) :
        return [ Messages.SHOW_INFO ]

    def handleNotification( self, notification ) :
        if notification.getName( ) == Messages.SHOW_INFO :
            title = notification.getBody( )[0]
            message = notification.getBody( )[1]
            showinfo( title,  message=message )

    def onRegister( self ) :
        pass

##
# Mediates an instance of tkinter's file dialog interface. Asks the user which file to download, and provides them with
# a browsing interface. For more information in tkinter, visit this site: http://www.tkdocs.com/
#
# @see patterns.mediator.Mediator
##
class FileDialogMediator( patterns.mediator.Mediator ) :
    NAME = "FileDialogMediator"

    def __init__( self, viewComponent ) :
        super( ).__init__( FileDialogMediator.NAME, viewComponent )

    def listNotificationInterests( self ) :
        return [ Messages.FIND_FILES ]

    def handleNotification( self, notification ) :
        if notification.getName( ) == Messages.FIND_FILES :
            vo = notification.getBody()
            dfile = filedialog.askopenfile( mode='r', title=vo.msg )
            if dfile != None :
                vo.path = dfile.name
                vo.entry.delete( 0, END )
                vo.entry.insert( 0, vo.path )

    def onRegister( self ) :
        pass

