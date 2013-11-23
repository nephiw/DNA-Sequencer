import multiprocessing
from concrete import views
from concrete import controller
from comm.messages import Messages
from concrete import async
import patterns.facade

##
#The main entry point of the application.  It creates the root of the gui tree, and initializes the \ref Controller
#extends the \ref Facade to provide the application specific logic.
##
#noinspection PyInitNewSignature
class EntryPoint( patterns.facade.Facade ) :

    ##
    #Since the initializeFacade method is overridden, EntryPoint will call it instead of the super constructor.
    ##
    def __init__( self ) :
        self.initializeFacade()
    ##
    # The singleton accessor for the applications concrete facade: EntryPoint.
    ##
    @staticmethod
    def getInstance() :
        return EntryPoint()

    ##
    #Override the patterns.facade.Facade.initializeFacade in order have greater control over the \ref Controller initialization.
    ##
    def initializeFacade( self ) :
        super().initializeFacade()
        self.initializeController()

    ##
    # Override the patterns.facade.Facade.initializeController in order to create the Controllers Command map.
    # This needs to happen before the other actors are created so that we can use Commands to handle this operation.
    #
    # @see patterns.facade.Facade
    # @see patterns.command.SimpleCommand
    # @see core.Controller
    ##
    def initializeController( self ) :
        patterns.facade.Facade.initializeController( self )

        self.registerCommand( Messages.STARTUP, controller.StartupCommand )
        self.registerCommand( Messages.START, controller.StartAlignmentCommand )
        self.registerCommand( Messages.STORE_VIEW_STATE, controller.SaveViewStateCommand )
        self.registerCommand( Messages.GET_CUSTOM_SUB_MATRIX, controller.ParseMatrixCommand )
        self.registerCommand( Messages.GET_STORED_SUB_MATRIX, controller.ParseMatrixCommand )
        self.registerCommand( Messages.RUN_PAIRWISE_ONLY, controller.PairwiseCompareCommand )
        self.registerCommand( Messages.RUN_PAIRWISE_MATRIX, async.CreateScoreMatrixCommand )
        self.registerCommand( Messages.EXTRACT_SEQUENCES, controller.ParseFastaCommand )
        self.registerCommand( Messages.BUILD_NEWICK_TREE, controller.BuildNewickTreeCommand )
        self.registerCommand( Messages.SHOW_TREE_GRAPHICALLY, controller.OpenTreeInForester )


    ##
    # This is the real entry point of the program, it is where the view tree gets started, and the first
    # EntryPoint gets instantiated.
    #
    # @see patterns.facade.Facade
    ##
if __name__ == "__main__" :
    # freeze support is needed to better handle errors that occur during multiprocessing.
    multiprocessing.freeze_support()
    entryPoint = EntryPoint.getInstance()
    gui = views.GraphicalUserInterface()
    entryPoint.sendNotification( Messages.STARTUP, gui )
    gui.mainloop()