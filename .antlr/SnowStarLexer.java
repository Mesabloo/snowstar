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
		COMMA=26, DOT=27, INLINE_COM=28, BEGIN_COM=29, END_COM=30, ASSIGN=31, 
		EQUALS=32, NEQUALS=33, GREATER=34, LOWER=35, GREATER_EQ=36, LOWER_EQ=37, 
		LOGIC_OR=38, LOGIC_AND=39, LOGIC_NOT=40, PLUS=41, MINUS=42, STAR=43, SLASH=44, 
		PERCENT=45, BIN_NOT=46, BIN_AND=47, BIN_OR=48, BIN_XOR=49, WS=50, COMMENT=51, 
		LINE_COMMENT=52, IDENTIFIER=53;
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
		"DOT", "INLINE_COM", "BEGIN_COM", "END_COM", "ASSIGN", "EQUALS", "NEQUALS", 
		"GREATER", "LOWER", "GREATER_EQ", "LOWER_EQ", "LOGIC_OR", "LOGIC_AND", 
		"LOGIC_NOT", "PLUS", "MINUS", "STAR", "SLASH", "PERCENT", "BIN_NOT", "BIN_AND", 
		"BIN_OR", "BIN_XOR", "WS", "COMMENT", "LINE_COMMENT", "IDENTIFIER", "EscapeSequence", 
		"HexDigits", "HexDigit", "BinDigits", "Digits", "LetterOrDigit", "Letter"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'bool'", "'char'", "'int8'", "'int16'", "'int32'", "'int64'", "'real16'", 
		"'real32'", "'real64'", "'void'", "'with'", null, null, null, null, null, 
		null, null, "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'.'", 
		"'\u00A7'", "'(*'", "'*)'", "'='", "'=='", "'!='", "'>'", "'<'", "'>='", 
		"'<='", "'||'", "'&&'", "'!'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", 
		"'&'", "'|'", "'^'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "BOOLEAN", "CHAR", "INTEGER8", "INTEGER16", "INTEGER32", "INTEGER64", 
		"REAL16", "REAL32", "REAL64", "VOID", "WITH", "DECIMAL_LITERAL", "HEX_LITERAL", 
		"BIN_LITERAL", "FLOAT_LITERAL", "BOOL_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", 
		"LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "SEMI", "COMMA", 
		"DOT", "INLINE_COM", "BEGIN_COM", "END_COM", "ASSIGN", "EQUALS", "NEQUALS", 
		"GREATER", "LOWER", "GREATER_EQ", "LOWER_EQ", "LOGIC_OR", "LOGIC_AND", 
		"LOGIC_NOT", "PLUS", "MINUS", "STAR", "SLASH", "PERCENT", "BIN_NOT", "BIN_AND", 
		"BIN_OR", "BIN_XOR", "WS", "COMMENT", "LINE_COMMENT", "IDENTIFIER"
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\67\u0191\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64"+
		"\t\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t"+
		"=\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\5\3\5"+
		"\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3"+
		"\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n"+
		"\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\r\6\r\u00bd\n"+
		"\r\r\r\16\r\u00be\3\16\3\16\3\16\6\16\u00c4\n\16\r\16\16\16\u00c5\3\17"+
		"\3\17\3\17\6\17\u00cb\n\17\r\17\16\17\u00cc\3\20\6\20\u00d0\n\20\r\20"+
		"\16\20\u00d1\3\20\3\20\7\20\u00d6\n\20\f\20\16\20\u00d9\13\20\3\20\3\20"+
		"\7\20\u00dd\n\20\f\20\16\20\u00e0\13\20\3\20\6\20\u00e3\n\20\r\20\16\20"+
		"\u00e4\3\20\3\20\5\20\u00e9\n\20\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3"+
		"\21\3\21\5\21\u00f4\n\21\3\22\3\22\3\22\5\22\u00f9\n\22\3\22\3\22\3\23"+
		"\3\23\3\23\7\23\u0100\n\23\f\23\16\23\u0103\13\23\3\23\3\23\3\24\3\24"+
		"\3\25\3\25\3\26\3\26\3\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3\33"+
		"\3\34\3\34\3\35\3\35\3\36\3\36\3\36\3\37\3\37\3\37\3 \3 \3!\3!\3!\3\""+
		"\3\"\3\"\3#\3#\3$\3$\3%\3%\3%\3&\3&\3&\3\'\3\'\3\'\3(\3(\3(\3)\3)\3*\3"+
		"*\3+\3+\3,\3,\3-\3-\3.\3.\3/\3/\3\60\3\60\3\61\3\61\3\62\3\62\3\63\6\63"+
		"\u014e\n\63\r\63\16\63\u014f\3\63\3\63\3\64\3\64\3\64\3\64\7\64\u0158"+
		"\n\64\f\64\16\64\u015b\13\64\3\64\3\64\3\64\3\64\3\64\3\65\3\65\7\65\u0164"+
		"\n\65\f\65\16\65\u0167\13\65\3\65\3\65\3\66\3\66\7\66\u016d\n\66\f\66"+
		"\16\66\u0170\13\66\3\67\3\67\3\67\38\38\78\u0177\n8\f8\168\u017a\138\3"+
		"9\39\3:\3:\7:\u0180\n:\f:\16:\u0183\13:\3;\3;\7;\u0187\n;\f;\16;\u018a"+
		"\13;\3<\3<\5<\u018e\n<\3=\3=\6\u0159\u0178\u0181\u0188\2>\3\3\5\4\7\5"+
		"\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23"+
		"%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G"+
		"%I&K\'M(O)Q*S+U,W-Y.[/]\60_\61a\62c\63e\64g\65i\66k\67m\2o\2q\2s\2u\2"+
		"w\2y\2\3\2\r\4\2ZZzz\4\2DDdd\6\2\f\f\17\17))^^\6\2\f\f\17\17$$^^\5\2\13"+
		"\f\16\17\"\"\4\2\f\f\17\17\n\2$$))^^ddhhppttvv\5\2\62;CHch\3\2\62\63\3"+
		"\2\62;\5\2C\\aac|\2\u019e\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2"+
		"\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2"+
		"\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3"+
		"\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2"+
		"\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67"+
		"\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2"+
		"\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2"+
		"\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]"+
		"\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2"+
		"\2\2\2k\3\2\2\2\3{\3\2\2\2\5\u0080\3\2\2\2\7\u0085\3\2\2\2\t\u008a\3\2"+
		"\2\2\13\u0090\3\2\2\2\r\u0096\3\2\2\2\17\u009c\3\2\2\2\21\u00a3\3\2\2"+
		"\2\23\u00aa\3\2\2\2\25\u00b1\3\2\2\2\27\u00b6\3\2\2\2\31\u00bc\3\2\2\2"+
		"\33\u00c0\3\2\2\2\35\u00c7\3\2\2\2\37\u00e8\3\2\2\2!\u00f3\3\2\2\2#\u00f5"+
		"\3\2\2\2%\u00fc\3\2\2\2\'\u0106\3\2\2\2)\u0108\3\2\2\2+\u010a\3\2\2\2"+
		"-\u010c\3\2\2\2/\u010e\3\2\2\2\61\u0110\3\2\2\2\63\u0112\3\2\2\2\65\u0114"+
		"\3\2\2\2\67\u0116\3\2\2\29\u0118\3\2\2\2;\u011a\3\2\2\2=\u011d\3\2\2\2"+
		"?\u0120\3\2\2\2A\u0122\3\2\2\2C\u0125\3\2\2\2E\u0128\3\2\2\2G\u012a\3"+
		"\2\2\2I\u012c\3\2\2\2K\u012f\3\2\2\2M\u0132\3\2\2\2O\u0135\3\2\2\2Q\u0138"+
		"\3\2\2\2S\u013a\3\2\2\2U\u013c\3\2\2\2W\u013e\3\2\2\2Y\u0140\3\2\2\2["+
		"\u0142\3\2\2\2]\u0144\3\2\2\2_\u0146\3\2\2\2a\u0148\3\2\2\2c\u014a\3\2"+
		"\2\2e\u014d\3\2\2\2g\u0153\3\2\2\2i\u0161\3\2\2\2k\u016a\3\2\2\2m\u0171"+
		"\3\2\2\2o\u0174\3\2\2\2q\u017b\3\2\2\2s\u017d\3\2\2\2u\u0184\3\2\2\2w"+
		"\u018d\3\2\2\2y\u018f\3\2\2\2{|\7d\2\2|}\7q\2\2}~\7q\2\2~\177\7n\2\2\177"+
		"\4\3\2\2\2\u0080\u0081\7e\2\2\u0081\u0082\7j\2\2\u0082\u0083\7c\2\2\u0083"+
		"\u0084\7t\2\2\u0084\6\3\2\2\2\u0085\u0086\7k\2\2\u0086\u0087\7p\2\2\u0087"+
		"\u0088\7v\2\2\u0088\u0089\7:\2\2\u0089\b\3\2\2\2\u008a\u008b\7k\2\2\u008b"+
		"\u008c\7p\2\2\u008c\u008d\7v\2\2\u008d\u008e\7\63\2\2\u008e\u008f\78\2"+
		"\2\u008f\n\3\2\2\2\u0090\u0091\7k\2\2\u0091\u0092\7p\2\2\u0092\u0093\7"+
		"v\2\2\u0093\u0094\7\65\2\2\u0094\u0095\7\64\2\2\u0095\f\3\2\2\2\u0096"+
		"\u0097\7k\2\2\u0097\u0098\7p\2\2\u0098\u0099\7v\2\2\u0099\u009a\78\2\2"+
		"\u009a\u009b\7\66\2\2\u009b\16\3\2\2\2\u009c\u009d\7t\2\2\u009d\u009e"+
		"\7g\2\2\u009e\u009f\7c\2\2\u009f\u00a0\7n\2\2\u00a0\u00a1\7\63\2\2\u00a1"+
		"\u00a2\78\2\2\u00a2\20\3\2\2\2\u00a3\u00a4\7t\2\2\u00a4\u00a5\7g\2\2\u00a5"+
		"\u00a6\7c\2\2\u00a6\u00a7\7n\2\2\u00a7\u00a8\7\65\2\2\u00a8\u00a9\7\64"+
		"\2\2\u00a9\22\3\2\2\2\u00aa\u00ab\7t\2\2\u00ab\u00ac\7g\2\2\u00ac\u00ad"+
		"\7c\2\2\u00ad\u00ae\7n\2\2\u00ae\u00af\78\2\2\u00af\u00b0\7\66\2\2\u00b0"+
		"\24\3\2\2\2\u00b1\u00b2\7x\2\2\u00b2\u00b3\7q\2\2\u00b3\u00b4\7k\2\2\u00b4"+
		"\u00b5\7f\2\2\u00b5\26\3\2\2\2\u00b6\u00b7\7y\2\2\u00b7\u00b8\7k\2\2\u00b8"+
		"\u00b9\7v\2\2\u00b9\u00ba\7j\2\2\u00ba\30\3\2\2\2\u00bb\u00bd\5u;\2\u00bc"+
		"\u00bb\3\2\2\2\u00bd\u00be\3\2\2\2\u00be\u00bc\3\2\2\2\u00be\u00bf\3\2"+
		"\2\2\u00bf\32\3\2\2\2\u00c0\u00c1\7\62\2\2\u00c1\u00c3\t\2\2\2\u00c2\u00c4"+
		"\5o8\2\u00c3\u00c2\3\2\2\2\u00c4\u00c5\3\2\2\2\u00c5\u00c3\3\2\2\2\u00c5"+
		"\u00c6\3\2\2\2\u00c6\34\3\2\2\2\u00c7\u00c8\7\62\2\2\u00c8\u00ca\t\3\2"+
		"\2\u00c9\u00cb\5s:\2\u00ca\u00c9\3\2\2\2\u00cb\u00cc\3\2\2\2\u00cc\u00ca"+
		"\3\2\2\2\u00cc\u00cd\3\2\2\2\u00cd\36\3\2\2\2\u00ce\u00d0\5u;\2\u00cf"+
		"\u00ce\3\2\2\2\u00d0\u00d1\3\2\2\2\u00d1\u00cf\3\2\2\2\u00d1\u00d2\3\2"+
		"\2\2\u00d2\u00d3\3\2\2\2\u00d3\u00d7\7\60\2\2\u00d4\u00d6\5u;\2\u00d5"+
		"\u00d4\3\2\2\2\u00d6\u00d9\3\2\2\2\u00d7\u00d5\3\2\2\2\u00d7\u00d8\3\2"+
		"\2\2\u00d8\u00e9\3\2\2\2\u00d9\u00d7\3\2\2\2\u00da\u00de\7\60\2\2\u00db"+
		"\u00dd\5u;\2\u00dc\u00db\3\2\2\2\u00dd\u00e0\3\2\2\2\u00de\u00dc\3\2\2"+
		"\2\u00de\u00df\3\2\2\2\u00df\u00e9\3\2\2\2\u00e0\u00de\3\2\2\2\u00e1\u00e3"+
		"\5u;\2\u00e2\u00e1\3\2\2\2\u00e3\u00e4\3\2\2\2\u00e4\u00e2\3\2\2\2\u00e4"+
		"\u00e5\3\2\2\2\u00e5\u00e6\3\2\2\2\u00e6\u00e7\7\60\2\2\u00e7\u00e9\3"+
		"\2\2\2\u00e8\u00cf\3\2\2\2\u00e8\u00da\3\2\2\2\u00e8\u00e2\3\2\2\2\u00e9"+
		" \3\2\2\2\u00ea\u00eb\7v\2\2\u00eb\u00ec\7t\2\2\u00ec\u00ed\7w\2\2\u00ed"+
		"\u00f4\7g\2\2\u00ee\u00ef\7h\2\2\u00ef\u00f0\7c\2\2\u00f0\u00f1\7n\2\2"+
		"\u00f1\u00f2\7u\2\2\u00f2\u00f4\7g\2\2\u00f3\u00ea\3\2\2\2\u00f3\u00ee"+
		"\3\2\2\2\u00f4\"\3\2\2\2\u00f5\u00f8\7)\2\2\u00f6\u00f9\n\4\2\2\u00f7"+
		"\u00f9\5m\67\2\u00f8\u00f6\3\2\2\2\u00f8\u00f7\3\2\2\2\u00f9\u00fa\3\2"+
		"\2\2\u00fa\u00fb\7)\2\2\u00fb$\3\2\2\2\u00fc\u0101\7$\2\2\u00fd\u0100"+
		"\n\5\2\2\u00fe\u0100\5m\67\2\u00ff\u00fd\3\2\2\2\u00ff\u00fe\3\2\2\2\u0100"+
		"\u0103\3\2\2\2\u0101\u00ff\3\2\2\2\u0101\u0102\3\2\2\2\u0102\u0104\3\2"+
		"\2\2\u0103\u0101\3\2\2\2\u0104\u0105\7$\2\2\u0105&\3\2\2\2\u0106\u0107"+
		"\7*\2\2\u0107(\3\2\2\2\u0108\u0109\7+\2\2\u0109*\3\2\2\2\u010a\u010b\7"+
		"}\2\2\u010b,\3\2\2\2\u010c\u010d\7\177\2\2\u010d.\3\2\2\2\u010e\u010f"+
		"\7]\2\2\u010f\60\3\2\2\2\u0110\u0111\7_\2\2\u0111\62\3\2\2\2\u0112\u0113"+
		"\7=\2\2\u0113\64\3\2\2\2\u0114\u0115\7.\2\2\u0115\66\3\2\2\2\u0116\u0117"+
		"\7\60\2\2\u01178\3\2\2\2\u0118\u0119\7\u00a9\2\2\u0119:\3\2\2\2\u011a"+
		"\u011b\7*\2\2\u011b\u011c\7,\2\2\u011c<\3\2\2\2\u011d\u011e\7,\2\2\u011e"+
		"\u011f\7+\2\2\u011f>\3\2\2\2\u0120\u0121\7?\2\2\u0121@\3\2\2\2\u0122\u0123"+
		"\7?\2\2\u0123\u0124\7?\2\2\u0124B\3\2\2\2\u0125\u0126\7#\2\2\u0126\u0127"+
		"\7?\2\2\u0127D\3\2\2\2\u0128\u0129\7@\2\2\u0129F\3\2\2\2\u012a\u012b\7"+
		">\2\2\u012bH\3\2\2\2\u012c\u012d\7@\2\2\u012d\u012e\7?\2\2\u012eJ\3\2"+
		"\2\2\u012f\u0130\7>\2\2\u0130\u0131\7?\2\2\u0131L\3\2\2\2\u0132\u0133"+
		"\7~\2\2\u0133\u0134\7~\2\2\u0134N\3\2\2\2\u0135\u0136\7(\2\2\u0136\u0137"+
		"\7(\2\2\u0137P\3\2\2\2\u0138\u0139\7#\2\2\u0139R\3\2\2\2\u013a\u013b\7"+
		"-\2\2\u013bT\3\2\2\2\u013c\u013d\7/\2\2\u013dV\3\2\2\2\u013e\u013f\7,"+
		"\2\2\u013fX\3\2\2\2\u0140\u0141\7\61\2\2\u0141Z\3\2\2\2\u0142\u0143\7"+
		"\'\2\2\u0143\\\3\2\2\2\u0144\u0145\7\u0080\2\2\u0145^\3\2\2\2\u0146\u0147"+
		"\7(\2\2\u0147`\3\2\2\2\u0148\u0149\7~\2\2\u0149b\3\2\2\2\u014a\u014b\7"+
		"`\2\2\u014bd\3\2\2\2\u014c\u014e\t\6\2\2\u014d\u014c\3\2\2\2\u014e\u014f"+
		"\3\2\2\2\u014f\u014d\3\2\2\2\u014f\u0150\3\2\2\2\u0150\u0151\3\2\2\2\u0151"+
		"\u0152\b\63\2\2\u0152f\3\2\2\2\u0153\u0154\7*\2\2\u0154\u0155\7,\2\2\u0155"+
		"\u0159\3\2\2\2\u0156\u0158\13\2\2\2\u0157\u0156\3\2\2\2\u0158\u015b\3"+
		"\2\2\2\u0159\u015a\3\2\2\2\u0159\u0157\3\2\2\2\u015a\u015c\3\2\2\2\u015b"+
		"\u0159\3\2\2\2\u015c\u015d\7,\2\2\u015d\u015e\7+\2\2\u015e\u015f\3\2\2"+
		"\2\u015f\u0160\b\64\2\2\u0160h\3\2\2\2\u0161\u0165\7\u00a9\2\2\u0162\u0164"+
		"\n\7\2\2\u0163\u0162\3\2\2\2\u0164\u0167\3\2\2\2\u0165\u0163\3\2\2\2\u0165"+
		"\u0166\3\2\2\2\u0166\u0168\3\2\2\2\u0167\u0165\3\2\2\2\u0168\u0169\b\65"+
		"\2\2\u0169j\3\2\2\2\u016a\u016e\5y=\2\u016b\u016d\5w<\2\u016c\u016b\3"+
		"\2\2\2\u016d\u0170\3\2\2\2\u016e\u016c\3\2\2\2\u016e\u016f\3\2\2\2\u016f"+
		"l\3\2\2\2\u0170\u016e\3\2\2\2\u0171\u0172\7^\2\2\u0172\u0173\t\b\2\2\u0173"+
		"n\3\2\2\2\u0174\u0178\5q9\2\u0175\u0177\5q9\2\u0176\u0175\3\2\2\2\u0177"+
		"\u017a\3\2\2\2\u0178\u0179\3\2\2\2\u0178\u0176\3\2\2\2\u0179p\3\2\2\2"+
		"\u017a\u0178\3\2\2\2\u017b\u017c\t\t\2\2\u017cr\3\2\2\2\u017d\u0181\t"+
		"\n\2\2\u017e\u0180\t\n\2\2\u017f\u017e\3\2\2\2\u0180\u0183\3\2\2\2\u0181"+
		"\u0182\3\2\2\2\u0181\u017f\3\2\2\2\u0182t\3\2\2\2\u0183\u0181\3\2\2\2"+
		"\u0184\u0188\t\13\2\2\u0185\u0187\t\13\2\2\u0186\u0185\3\2\2\2\u0187\u018a"+
		"\3\2\2\2\u0188\u0189\3\2\2\2\u0188\u0186\3\2\2\2\u0189v\3\2\2\2\u018a"+
		"\u0188\3\2\2\2\u018b\u018e\5y=\2\u018c\u018e\t\13\2\2\u018d\u018b\3\2"+
		"\2\2\u018d\u018c\3\2\2\2\u018ex\3\2\2\2\u018f\u0190\t\f\2\2\u0190z\3\2"+
		"\2\2\27\2\u00be\u00c5\u00cc\u00d1\u00d7\u00de\u00e4\u00e8\u00f3\u00f8"+
		"\u00ff\u0101\u014f\u0159\u0165\u016e\u0178\u0181\u0188\u018d\3\2\3\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}