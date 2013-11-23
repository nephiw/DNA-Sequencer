##
# A library of message types, the strings stored here are used to determine what the \ref Notification is within
# the system.  This is the standard location for all messages passed around in the application.
class Messages :
    MAIN_WINDOW_BUILT = 'mainWindowBuilt'
    STARTUP = 'startup'
    START = 'start'
    FIND_FILES = 'findFiles'
    STORE_CURRENT_STATE = 'storeCurrentState'
    STORE_VIEW_STATE = 'storeViewState'
    RUN_PAIRWISE_MATRIX = 'runPairwiseMatrix'
    RUN_PAIRWISE_ONLY = 'runPairwiseOnly'
    GET_CUSTOM_SUB_MATRIX = 'getCustomSubMatrix'
    GET_STORED_SUB_MATRIX = 'getStoredSubMatrix'
    EXTRACT_SEQUENCES = 'extractSequences'
    SHOW_RESULTS = 'showResults'
    BUILD_NEWICK_TREE = 'buildNewickTree'
    SHOW_TREE_GRAPHICALLY = 'showTreeGraphically'
    SHOW_INFO = 'showInfo'
    UPDATE_STATUS_TEXT = 'updateStatusText'