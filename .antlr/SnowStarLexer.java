// Generated from /home/mesabloo/Documents/snowstar_reborn/SnowStarLexer.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class SnowStarLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		BOOLEAN=1, CHAR=2, INTEGER8=3, INTEGER16=4, INTEGER32=5, INTEGER64=6, 
		REAL16=7, REAL32=8, REAL64=9, VOID=10, WITH=11, DECIMAL_LITERAL=12, HEX_LITERAL=13, 
		BIN_LITERAL=14, FLOAT_LITERAL=15, BOOL_LITERAL=16, CHAR_LITERAL=17, STRING_LITERAL=18, 
		LPAREN=19, RPAREN=20, LBRACE=21, RBRACE=22, LBRACK=23, RBRACK=24, SEMI=25, 
		COMMA=26, DOT=27, ASSIGN=28, EQUALS=29, NEQUALS=30, GREATER=31, LOWER=32, 
		GREATER_EQ=33, LOWER_EQ=34, LOGIC_OR=35, LOGIC_AND=36, LOGIC_NOT=37, PLUS=38, 
		MINUS=39, STAR=40, SLASH=41, PERCENT=42, BIN_NOT=43, BIN_AND=44, BIN_OR=45, 
		BIN_XOR=46, WS=47, COMMENT=48, LINE_COMMENT=49, IDENTIFIER=50;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"BOOLEAN", "CHAR", "INTEGER8", "INTEGER16", "INTEGER32", "INTEGER64", 
		"REAL16", "REAL32", "REAL64", "VOID", "WITH", "DECIMAL_LITERAL", "HEX_LITERAL", 
		"BIN_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", 
		"LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "SEMI", "COMMA", 
		"DOT", "ASSIGN", "EQUALS", "NEQUALS", "GREATER", "LOWER", "GREATER_EQ", 
		"LOWER_EQ", "LOGIC_OR", "LOGIC_AND", "LOGIC_NOT", "PLUS", "MINUS", "STAR", 
		"SLASH", "PERCENT", "BIN_NOT", "BIN_AND", "BIN_OR", "BIN_XOR", "WS", "COMMENT", 
		"LINE_COMMENT", "IDENTIFIER", "EscapeSequence", "HexDigits", "HexDigit", 
		"BinDigits", "Digits", "LetterOrDigit", "Letter"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'bool'", "'char'", "'int8'", "'int16'", "'int32'", "'int64'", "'real16'", 
		"'real32'", "'real64'", "'void'", "'with'", null, null, null, null, null, 
		null, null, "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'.'", 
		"'='", "'=='", "'!='", "'>'", "'<'", "'>='", "'<='", "'||'", "'&&'", "'!'", 
		"'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'&'", "'|'", "'^'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "BOOLEAN", "CHAR", "INTEGER8", "INTEGER16", "INTEGER32", "INTEGER64", 
		"REAL16", "REAL32", "REAL64", "VOID", "WITH", "DECIMAL_LITERAL", "HEX_LITERAL", 
		"BIN_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", 
		"LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "SEMI", "COMMA", 
		"DOT", "ASSIGN", "EQUALS", "NEQUALS", "GREATER", "LOWER", "GREATER_EQ", 
		"LOWER_EQ", "LOGIC_OR", "LOGIC_AND", "LOGIC_NOT", "PLUS", "MINUS", "STAR", 
		"SLASH", "PERCENT", "BIN_NOT", "BIN_AND", "BIN_OR", "BIN_XOR", "WS", "COMMENT", 
		"LINE_COMMENT", "IDENTIFIER"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public SnowStarLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "SnowStarLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\64\u0183\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64"+
		"\t\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\3\2\3\2\3\2\3\2"+
		"\3\2\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3"+
		"\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b"+
		"\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13"+
		"\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\r\6\r\u00b7\n\r\r\r\16\r\u00b8\3"+
		"\16\3\16\3\16\6\16\u00be\n\16\r\16\16\16\u00bf\3\17\3\17\3\17\6\17\u00c5"+
		"\n\17\r\17\16\17\u00c6\3\20\6\20\u00ca\n\20\r\20\16\20\u00cb\3\20\3\20"+
		"\7\20\u00d0\n\20\f\20\16\20\u00d3\13\20\3\20\3\20\7\20\u00d7\n\20\f\20"+
		"\16\20\u00da\13\20\3\20\6\20\u00dd\n\20\r\20\16\20\u00de\3\20\3\20\5\20"+
		"\u00e3\n\20\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\21\5\21\u00ee\n"+
		"\21\3\22\3\22\3\22\5\22\u00f3\n\22\3\22\3\22\3\23\3\23\3\23\7\23\u00fa"+
		"\n\23\f\23\16\23\u00fd\13\23\3\23\3\23\3\24\3\24\3\25\3\25\3\26\3\26\3"+
		"\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3\35\3"+
		"\36\3\36\3\36\3\37\3\37\3\37\3 \3 \3!\3!\3\"\3\"\3\"\3#\3#\3#\3$\3$\3"+
		"$\3%\3%\3%\3&\3&\3\'\3\'\3(\3(\3)\3)\3*\3*\3+\3+\3,\3,\3-\3-\3.\3.\3/"+
		"\3/\3\60\6\60\u0140\n\60\r\60\16\60\u0141\3\60\3\60\3\61\3\61\3\61\3\61"+
		"\7\61\u014a\n\61\f\61\16\61\u014d\13\61\3\61\3\61\3\61\3\61\3\61\3\62"+
		"\3\62\7\62\u0156\n\62\f\62\16\62\u0159\13\62\3\62\3\62\3\63\3\63\7\63"+
		"\u015f\n\63\f\63\16\63\u0162\13\63\3\64\3\64\3\64\3\65\3\65\7\65\u0169"+
		"\n\65\f\65\16\65\u016c\13\65\3\66\3\66\3\67\3\67\7\67\u0172\n\67\f\67"+
		"\16\67\u0175\13\67\38\38\78\u0179\n8\f8\168\u017c\138\39\39\59\u0180\n"+
		"9\3:\3:\6\u014b\u016a\u0173\u017a\2;\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21"+
		"\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30"+
		"/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(O)Q*S+U,W-Y.["+
		"/]\60_\61a\62c\63e\64g\2i\2k\2m\2o\2q\2s\2\3\2\r\4\2ZZzz\4\2DDdd\6\2\f"+
		"\f\17\17))^^\6\2\f\f\17\17$$^^\5\2\13\f\16\17\"\"\4\2\f\f\17\17\n\2$$"+
		"))^^ddhhppttvv\5\2\62;CHch\3\2\62\63\3\2\62;\5\2C\\aac|\2\u0190\2\3\3"+
		"\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2"+
		"\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3"+
		"\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2"+
		"%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61"+
		"\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2"+
		"\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I"+
		"\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2"+
		"\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2"+
		"\2c\3\2\2\2\2e\3\2\2\2\3u\3\2\2\2\5z\3\2\2\2\7\177\3\2\2\2\t\u0084\3\2"+
		"\2\2\13\u008a\3\2\2\2\r\u0090\3\2\2\2\17\u0096\3\2\2\2\21\u009d\3\2\2"+
		"\2\23\u00a4\3\2\2\2\25\u00ab\3\2\2\2\27\u00b0\3\2\2\2\31\u00b6\3\2\2\2"+
		"\33\u00ba\3\2\2\2\35\u00c1\3\2\2\2\37\u00e2\3\2\2\2!\u00ed\3\2\2\2#\u00ef"+
		"\3\2\2\2%\u00f6\3\2\2\2\'\u0100\3\2\2\2)\u0102\3\2\2\2+\u0104\3\2\2\2"+
		"-\u0106\3\2\2\2/\u0108\3\2\2\2\61\u010a\3\2\2\2\63\u010c\3\2\2\2\65\u010e"+
		"\3\2\2\2\67\u0110\3\2\2\29\u0112\3\2\2\2;\u0114\3\2\2\2=\u0117\3\2\2\2"+
		"?\u011a\3\2\2\2A\u011c\3\2\2\2C\u011e\3\2\2\2E\u0121\3\2\2\2G\u0124\3"+
		"\2\2\2I\u0127\3\2\2\2K\u012a\3\2\2\2M\u012c\3\2\2\2O\u012e\3\2\2\2Q\u0130"+
		"\3\2\2\2S\u0132\3\2\2\2U\u0134\3\2\2\2W\u0136\3\2\2\2Y\u0138\3\2\2\2["+
		"\u013a\3\2\2\2]\u013c\3\2\2\2_\u013f\3\2\2\2a\u0145\3\2\2\2c\u0153\3\2"+
		"\2\2e\u015c\3\2\2\2g\u0163\3\2\2\2i\u0166\3\2\2\2k\u016d\3\2\2\2m\u016f"+
		"\3\2\2\2o\u0176\3\2\2\2q\u017f\3\2\2\2s\u0181\3\2\2\2uv\7d\2\2vw\7q\2"+
		"\2wx\7q\2\2xy\7n\2\2y\4\3\2\2\2z{\7e\2\2{|\7j\2\2|}\7c\2\2}~\7t\2\2~\6"+
		"\3\2\2\2\177\u0080\7k\2\2\u0080\u0081\7p\2\2\u0081\u0082\7v\2\2\u0082"+
		"\u0083\7:\2\2\u0083\b\3\2\2\2\u0084\u0085\7k\2\2\u0085\u0086\7p\2\2\u0086"+
		"\u0087\7v\2\2\u0087\u0088\7\63\2\2\u0088\u0089\78\2\2\u0089\n\3\2\2\2"+
		"\u008a\u008b\7k\2\2\u008b\u008c\7p\2\2\u008c\u008d\7v\2\2\u008d\u008e"+
		"\7\65\2\2\u008e\u008f\7\64\2\2\u008f\f\3\2\2\2\u0090\u0091\7k\2\2\u0091"+
		"\u0092\7p\2\2\u0092\u0093\7v\2\2\u0093\u0094\78\2\2\u0094\u0095\7\66\2"+
		"\2\u0095\16\3\2\2\2\u0096\u0097\7t\2\2\u0097\u0098\7g\2\2\u0098\u0099"+
		"\7c\2\2\u0099\u009a\7n\2\2\u009a\u009b\7\63\2\2\u009b\u009c\78\2\2\u009c"+
		"\20\3\2\2\2\u009d\u009e\7t\2\2\u009e\u009f\7g\2\2\u009f\u00a0\7c\2\2\u00a0"+
		"\u00a1\7n\2\2\u00a1\u00a2\7\65\2\2\u00a2\u00a3\7\64\2\2\u00a3\22\3\2\2"+
		"\2\u00a4\u00a5\7t\2\2\u00a5\u00a6\7g\2\2\u00a6\u00a7\7c\2\2\u00a7\u00a8"+
		"\7n\2\2\u00a8\u00a9\78\2\2\u00a9\u00aa\7\66\2\2\u00aa\24\3\2\2\2\u00ab"+
		"\u00ac\7x\2\2\u00ac\u00ad\7q\2\2\u00ad\u00ae\7k\2\2\u00ae\u00af\7f\2\2"+
		"\u00af\26\3\2\2\2\u00b0\u00b1\7y\2\2\u00b1\u00b2\7k\2\2\u00b2\u00b3\7"+
		"v\2\2\u00b3\u00b4\7j\2\2\u00b4\30\3\2\2\2\u00b5\u00b7\5o8\2\u00b6\u00b5"+
		"\3\2\2\2\u00b7\u00b8\3\2\2\2\u00b8\u00b6\3\2\2\2\u00b8\u00b9\3\2\2\2\u00b9"+
		"\32\3\2\2\2\u00ba\u00bb\7\62\2\2\u00bb\u00bd\t\2\2\2\u00bc\u00be\5i\65"+
		"\2\u00bd\u00bc\3\2\2\2\u00be\u00bf\3\2\2\2\u00bf\u00bd\3\2\2\2\u00bf\u00c0"+
		"\3\2\2\2\u00c0\34\3\2\2\2\u00c1\u00c2\7\62\2\2\u00c2\u00c4\t\3\2\2\u00c3"+
		"\u00c5\5m\67\2\u00c4\u00c3\3\2\2\2\u00c5\u00c6\3\2\2\2\u00c6\u00c4\3\2"+
		"\2\2\u00c6\u00c7\3\2\2\2\u00c7\36\3\2\2\2\u00c8\u00ca\5o8\2\u00c9\u00c8"+
		"\3\2\2\2\u00ca\u00cb\3\2\2\2\u00cb\u00c9\3\2\2\2\u00cb\u00cc\3\2\2\2\u00cc"+
		"\u00cd\3\2\2\2\u00cd\u00d1\7\60\2\2\u00ce\u00d0\5o8\2\u00cf\u00ce\3\2"+
		"\2\2\u00d0\u00d3\3\2\2\2\u00d1\u00cf\3\2\2\2\u00d1\u00d2\3\2\2\2\u00d2"+
		"\u00e3\3\2\2\2\u00d3\u00d1\3\2\2\2\u00d4\u00d8\7\60\2\2\u00d5\u00d7\5"+
		"o8\2\u00d6\u00d5\3\2\2\2\u00d7\u00da\3\2\2\2\u00d8\u00d6\3\2\2\2\u00d8"+
		"\u00d9\3\2\2\2\u00d9\u00e3\3\2\2\2\u00da\u00d8\3\2\2\2\u00db\u00dd\5o"+
		"8\2\u00dc\u00db\3\2\2\2\u00dd\u00de\3\2\2\2\u00de\u00dc\3\2\2\2\u00de"+
		"\u00df\3\2\2\2\u00df\u00e0\3\2\2\2\u00e0\u00e1\7\60\2\2\u00e1\u00e3\3"+
		"\2\2\2\u00e2\u00c9\3\2\2\2\u00e2\u00d4\3\2\2\2\u00e2\u00dc\3\2\2\2\u00e3"+
		" \3\2\2\2\u00e4\u00e5\7v\2\2\u00e5\u00e6\7t\2\2\u00e6\u00e7\7w\2\2\u00e7"+
		"\u00ee\7g\2\2\u00e8\u00e9\7h\2\2\u00e9\u00ea\7c\2\2\u00ea\u00eb\7n\2\2"+
		"\u00eb\u00ec\7u\2\2\u00ec\u00ee\7g\2\2\u00ed\u00e4\3\2\2\2\u00ed\u00e8"+
		"\3\2\2\2\u00ee\"\3\2\2\2\u00ef\u00f2\7)\2\2\u00f0\u00f3\n\4\2\2\u00f1"+
		"\u00f3\5g\64\2\u00f2\u00f0\3\2\2\2\u00f2\u00f1\3\2\2\2\u00f3\u00f4\3\2"+
		"\2\2\u00f4\u00f5\7)\2\2\u00f5$\3\2\2\2\u00f6\u00fb\7$\2\2\u00f7\u00fa"+
		"\n\5\2\2\u00f8\u00fa\5g\64\2\u00f9\u00f7\3\2\2\2\u00f9\u00f8\3\2\2\2\u00fa"+
		"\u00fd\3\2\2\2\u00fb\u00f9\3\2\2\2\u00fb\u00fc\3\2\2\2\u00fc\u00fe\3\2"+
		"\2\2\u00fd\u00fb\3\2\2\2\u00fe\u00ff\7$\2\2\u00ff&\3\2\2\2\u0100\u0101"+
		"\7*\2\2\u0101(\3\2\2\2\u0102\u0103\7+\2\2\u0103*\3\2\2\2\u0104\u0105\7"+
		"}\2\2\u0105,\3\2\2\2\u0106\u0107\7\177\2\2\u0107.\3\2\2\2\u0108\u0109"+
		"\7]\2\2\u0109\60\3\2\2\2\u010a\u010b\7_\2\2\u010b\62\3\2\2\2\u010c\u010d"+
		"\7=\2\2\u010d\64\3\2\2\2\u010e\u010f\7.\2\2\u010f\66\3\2\2\2\u0110\u0111"+
		"\7\60\2\2\u01118\3\2\2\2\u0112\u0113\7?\2\2\u0113:\3\2\2\2\u0114\u0115"+
		"\7?\2\2\u0115\u0116\7?\2\2\u0116<\3\2\2\2\u0117\u0118\7#\2\2\u0118\u0119"+
		"\7?\2\2\u0119>\3\2\2\2\u011a\u011b\7@\2\2\u011b@\3\2\2\2\u011c\u011d\7"+
		">\2\2\u011dB\3\2\2\2\u011e\u011f\7@\2\2\u011f\u0120\7?\2\2\u0120D\3\2"+
		"\2\2\u0121\u0122\7>\2\2\u0122\u0123\7?\2\2\u0123F\3\2\2\2\u0124\u0125"+
		"\7~\2\2\u0125\u0126\7~\2\2\u0126H\3\2\2\2\u0127\u0128\7(\2\2\u0128\u0129"+
		"\7(\2\2\u0129J\3\2\2\2\u012a\u012b\7#\2\2\u012bL\3\2\2\2\u012c\u012d\7"+
		"-\2\2\u012dN\3\2\2\2\u012e\u012f\7/\2\2\u012fP\3\2\2\2\u0130\u0131\7,"+
		"\2\2\u0131R\3\2\2\2\u0132\u0133\7\61\2\2\u0133T\3\2\2\2\u0134\u0135\7"+
		"\'\2\2\u0135V\3\2\2\2\u0136\u0137\7\u0080\2\2\u0137X\3\2\2\2\u0138\u0139"+
		"\7(\2\2\u0139Z\3\2\2\2\u013a\u013b\7~\2\2\u013b\\\3\2\2\2\u013c\u013d"+
		"\7`\2\2\u013d^\3\2\2\2\u013e\u0140\t\6\2\2\u013f\u013e\3\2\2\2\u0140\u0141"+
		"\3\2\2\2\u0141\u013f\3\2\2\2\u0141\u0142\3\2\2\2\u0142\u0143\3\2\2\2\u0143"+
		"\u0144\b\60\2\2\u0144`\3\2\2\2\u0145\u0146\7\60\2\2\u0146\u0147\7<\2\2"+
		"\u0147\u014b\3\2\2\2\u0148\u014a\13\2\2\2\u0149\u0148\3\2\2\2\u014a\u014d"+
		"\3\2\2\2\u014b\u014c\3\2\2\2\u014b\u0149\3\2\2\2\u014c\u014e\3\2\2\2\u014d"+
		"\u014b\3\2\2\2\u014e\u014f\7<\2\2\u014f\u0150\7\60\2\2\u0150\u0151\3\2"+
		"\2\2\u0151\u0152\b\61\2\2\u0152b\3\2\2\2\u0153\u0157\7\u00a9\2\2\u0154"+
		"\u0156\n\7\2\2\u0155\u0154\3\2\2\2\u0156\u0159\3\2\2\2\u0157\u0155\3\2"+
		"\2\2\u0157\u0158\3\2\2\2\u0158\u015a\3\2\2\2\u0159\u0157\3\2\2\2\u015a"+
		"\u015b\b\62\2\2\u015bd\3\2\2\2\u015c\u0160\5s:\2\u015d\u015f\5q9\2\u015e"+
		"\u015d\3\2\2\2\u015f\u0162\3\2\2\2\u0160\u015e\3\2\2\2\u0160\u0161\3\2"+
		"\2\2\u0161f\3\2\2\2\u0162\u0160\3\2\2\2\u0163\u0164\7^\2\2\u0164\u0165"+
		"\t\b\2\2\u0165h\3\2\2\2\u0166\u016a\5k\66\2\u0167\u0169\5k\66\2\u0168"+
		"\u0167\3\2\2\2\u0169\u016c\3\2\2\2\u016a\u016b\3\2\2\2\u016a\u0168\3\2"+
		"\2\2\u016bj\3\2\2\2\u016c\u016a\3\2\2\2\u016d\u016e\t\t\2\2\u016el\3\2"+
		"\2\2\u016f\u0173\t\n\2\2\u0170\u0172\t\n\2\2\u0171\u0170\3\2\2\2\u0172"+
		"\u0175\3\2\2\2\u0173\u0174\3\2\2\2\u0173\u0171\3\2\2\2\u0174n\3\2\2\2"+
		"\u0175\u0173\3\2\2\2\u0176\u017a\t\13\2\2\u0177\u0179\t\13\2\2\u0178\u0177"+
		"\3\2\2\2\u0179\u017c\3\2\2\2\u017a\u017b\3\2\2\2\u017a\u0178\3\2\2\2\u017b"+
		"p\3\2\2\2\u017c\u017a\3\2\2\2\u017d\u0180\5s:\2\u017e\u0180\t\13\2\2\u017f"+
		"\u017d\3\2\2\2\u017f\u017e\3\2\2\2\u0180r\3\2\2\2\u0181\u0182\t\f\2\2"+
		"\u0182t\3\2\2\2\27\2\u00b8\u00bf\u00c6\u00cb\u00d1\u00d8\u00de\u00e2\u00ed"+
		"\u00f2\u00f9\u00fb\u0141\u014b\u0157\u0160\u016a\u0173\u017a\u017f\3\2"+
		"\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}