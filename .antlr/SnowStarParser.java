// Generated from /home/mesabloo/Documents/snowstar_reborn/SnowStarParser.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class SnowStarParser extends Parser {
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
	public static final int
		RULE_compilationUnit = 0, RULE_statement = 1, RULE_expression = 2, RULE_assign = 3, 
		RULE_define = 4, RULE_declare = 5, RULE_declareNoID = 6, RULE_alias = 7, 
		RULE_literal = 8, RULE_type = 9;
	public static final String[] ruleNames = {
		"compilationUnit", "statement", "expression", "assign", "define", "declare", 
		"declareNoID", "alias", "literal", "type"
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

	@Override
	public String getGrammarFileName() { return "SnowStarParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public SnowStarParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class CompilationUnitContext extends ParserRuleContext {
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public CompilationUnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compilationUnit; }
	}

	public final CompilationUnitContext compilationUnit() throws RecognitionException {
		CompilationUnitContext _localctx = new CompilationUnitContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_compilationUnit);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(21); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(20);
				statement();
				}
				}
				setState(23); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << BOOLEAN) | (1L << CHAR) | (1L << INTEGER8) | (1L << INTEGER16) | (1L << INTEGER32) | (1L << INTEGER64) | (1L << REAL16) | (1L << REAL32) | (1L << REAL64) | (1L << VOID) | (1L << WITH) | (1L << IDENTIFIER))) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public Token eol;
		public DeclareContext declare() {
			return getRuleContext(DeclareContext.class,0);
		}
		public DefineContext define() {
			return getRuleContext(DefineContext.class,0);
		}
		public AliasContext alias() {
			return getRuleContext(AliasContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_statement);
		int _la;
		try {
			setState(37);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(25);
				declare();
				setState(27);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SEMI) {
					{
					setState(26);
					((StatementContext)_localctx).eol = match(SEMI);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(29);
				define();
				setState(31);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SEMI) {
					{
					setState(30);
					((StatementContext)_localctx).eol = match(SEMI);
					}
				}

				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(33);
				alias();
				setState(35);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SEMI) {
					{
					setState(34);
					((StatementContext)_localctx).eol = match(SEMI);
					}
				}

				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionContext extends ParserRuleContext {
		public Token lparen;
		public Token uop;
		public Token bop;
		public TerminalNode IDENTIFIER() { return getToken(SnowStarParser.IDENTIFIER, 0); }
		public LiteralContext literal() {
			return getRuleContext(LiteralContext.class,0);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	}

	public final ExpressionContext expression() throws RecognitionException {
		return expression(0);
	}

	private ExpressionContext expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpressionContext _localctx = new ExpressionContext(_ctx, _parentState);
		ExpressionContext _prevctx = _localctx;
		int _startState = 4;
		enterRecursionRule(_localctx, 4, RULE_expression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(52);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case DECIMAL_LITERAL:
			case HEX_LITERAL:
			case BIN_LITERAL:
			case FLOAT_LITERAL:
			case BOOL_LITERAL:
			case CHAR_LITERAL:
			case LPAREN:
			case IDENTIFIER:
				{
				setState(46);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case IDENTIFIER:
					{
					setState(40);
					match(IDENTIFIER);
					}
					break;
				case DECIMAL_LITERAL:
				case HEX_LITERAL:
				case BIN_LITERAL:
				case FLOAT_LITERAL:
				case BOOL_LITERAL:
				case CHAR_LITERAL:
					{
					setState(41);
					literal();
					}
					break;
				case LPAREN:
					{
					setState(42);
					((ExpressionContext)_localctx).lparen = match(LPAREN);
					setState(43);
					expression(0);
					setState(44);
					match(RPAREN);
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				break;
			case LOGIC_NOT:
			case PLUS:
			case MINUS:
			case BIN_NOT:
				{
				setState(48);
				((ExpressionContext)_localctx).uop = _input.LT(1);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LOGIC_NOT) | (1L << PLUS) | (1L << MINUS) | (1L << BIN_NOT))) != 0)) ) {
					((ExpressionContext)_localctx).uop = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(50);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,6,_ctx) ) {
				case 1:
					{
					setState(49);
					expression(0);
					}
					break;
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(76);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,13,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(74);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
					case 1:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(54);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(55);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==STAR || _la==SLASH) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(57);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
						case 1:
							{
							setState(56);
							expression(0);
							}
							break;
						}
						}
						break;
					case 2:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(59);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(60);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==PLUS || _la==MINUS) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(62);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,9,_ctx) ) {
						case 1:
							{
							setState(61);
							expression(0);
							}
							break;
						}
						}
						break;
					case 3:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(64);
						if (!(precpred(_ctx, 2))) throw new FailedPredicateException(this, "precpred(_ctx, 2)");
						setState(65);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << EQUALS) | (1L << NEQUALS) | (1L << GREATER) | (1L << LOWER) | (1L << GREATER_EQ) | (1L << LOWER_EQ))) != 0)) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(67);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
						case 1:
							{
							setState(66);
							expression(0);
							}
							break;
						}
						}
						break;
					case 4:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						pushNewRecursionContext(_localctx, _startState, RULE_expression);
						setState(69);
						if (!(precpred(_ctx, 1))) throw new FailedPredicateException(this, "precpred(_ctx, 1)");
						setState(70);
						((ExpressionContext)_localctx).bop = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LOGIC_OR) | (1L << LOGIC_AND) | (1L << BIN_AND) | (1L << BIN_OR) | (1L << BIN_XOR))) != 0)) ) {
							((ExpressionContext)_localctx).bop = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(72);
						_errHandler.sync(this);
						switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
						case 1:
							{
							setState(71);
							expression(0);
							}
							break;
						}
						}
						break;
					}
					} 
				}
				setState(78);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,13,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class AssignContext extends ParserRuleContext {
		public Token eop;
		public TerminalNode IDENTIFIER() { return getToken(SnowStarParser.IDENTIFIER, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public AssignContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assign; }
	}

	public final AssignContext assign() throws RecognitionException {
		AssignContext _localctx = new AssignContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_assign);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(79);
			match(IDENTIFIER);
			setState(81);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ASSIGN) {
				{
				setState(80);
				((AssignContext)_localctx).eop = match(ASSIGN);
				}
			}

			setState(84);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << DECIMAL_LITERAL) | (1L << HEX_LITERAL) | (1L << BIN_LITERAL) | (1L << FLOAT_LITERAL) | (1L << BOOL_LITERAL) | (1L << CHAR_LITERAL) | (1L << LPAREN) | (1L << LOGIC_NOT) | (1L << PLUS) | (1L << MINUS) | (1L << BIN_NOT) | (1L << IDENTIFIER))) != 0)) {
				{
				setState(83);
				expression(0);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DefineContext extends ParserRuleContext {
		public Token eop;
		public DeclareContext declare() {
			return getRuleContext(DeclareContext.class,0);
		}
		public DeclareNoIDContext declareNoID() {
			return getRuleContext(DeclareNoIDContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public DefineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_define; }
	}

	public final DefineContext define() throws RecognitionException {
		DefineContext _localctx = new DefineContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_define);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(88);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,16,_ctx) ) {
			case 1:
				{
				setState(86);
				declare();
				}
				break;
			case 2:
				{
				setState(87);
				declareNoID();
				}
				break;
			}
			setState(91);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ASSIGN) {
				{
				setState(90);
				((DefineContext)_localctx).eop = match(ASSIGN);
				}
			}

			setState(94);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				{
				setState(93);
				expression(0);
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclareContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(SnowStarParser.IDENTIFIER, 0); }
		public DeclareContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declare; }
	}

	public final DeclareContext declare() throws RecognitionException {
		DeclareContext _localctx = new DeclareContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_declare);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(96);
			type();
			setState(97);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclareNoIDContext extends ParserRuleContext {
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public DeclareNoIDContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declareNoID; }
	}

	public final DeclareNoIDContext declareNoID() throws RecognitionException {
		DeclareNoIDContext _localctx = new DeclareNoIDContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_declareNoID);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(99);
			type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AliasContext extends ParserRuleContext {
		public Token with;
		public Token eop;
		public TerminalNode IDENTIFIER() { return getToken(SnowStarParser.IDENTIFIER, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public AliasContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_alias; }
	}

	public final AliasContext alias() throws RecognitionException {
		AliasContext _localctx = new AliasContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_alias);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(101);
			((AliasContext)_localctx).with = match(WITH);
			setState(103);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				{
				setState(102);
				match(IDENTIFIER);
				}
				break;
			}
			setState(106);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ASSIGN) {
				{
				setState(105);
				((AliasContext)_localctx).eop = match(ASSIGN);
				}
			}

			setState(109);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,21,_ctx) ) {
			case 1:
				{
				setState(108);
				type();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LiteralContext extends ParserRuleContext {
		public TerminalNode DECIMAL_LITERAL() { return getToken(SnowStarParser.DECIMAL_LITERAL, 0); }
		public TerminalNode HEX_LITERAL() { return getToken(SnowStarParser.HEX_LITERAL, 0); }
		public TerminalNode BIN_LITERAL() { return getToken(SnowStarParser.BIN_LITERAL, 0); }
		public TerminalNode FLOAT_LITERAL() { return getToken(SnowStarParser.FLOAT_LITERAL, 0); }
		public TerminalNode BOOL_LITERAL() { return getToken(SnowStarParser.BOOL_LITERAL, 0); }
		public TerminalNode CHAR_LITERAL() { return getToken(SnowStarParser.CHAR_LITERAL, 0); }
		public LiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal; }
	}

	public final LiteralContext literal() throws RecognitionException {
		LiteralContext _localctx = new LiteralContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_literal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(111);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << DECIMAL_LITERAL) | (1L << HEX_LITERAL) | (1L << BIN_LITERAL) | (1L << FLOAT_LITERAL) | (1L << BOOL_LITERAL) | (1L << CHAR_LITERAL))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TypeContext extends ParserRuleContext {
		public TerminalNode BOOLEAN() { return getToken(SnowStarParser.BOOLEAN, 0); }
		public TerminalNode CHAR() { return getToken(SnowStarParser.CHAR, 0); }
		public TerminalNode INTEGER8() { return getToken(SnowStarParser.INTEGER8, 0); }
		public TerminalNode INTEGER16() { return getToken(SnowStarParser.INTEGER16, 0); }
		public TerminalNode INTEGER32() { return getToken(SnowStarParser.INTEGER32, 0); }
		public TerminalNode INTEGER64() { return getToken(SnowStarParser.INTEGER64, 0); }
		public TerminalNode REAL16() { return getToken(SnowStarParser.REAL16, 0); }
		public TerminalNode REAL32() { return getToken(SnowStarParser.REAL32, 0); }
		public TerminalNode REAL64() { return getToken(SnowStarParser.REAL64, 0); }
		public TerminalNode VOID() { return getToken(SnowStarParser.VOID, 0); }
		public TerminalNode IDENTIFIER() { return getToken(SnowStarParser.IDENTIFIER, 0); }
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(113);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << BOOLEAN) | (1L << CHAR) | (1L << INTEGER8) | (1L << INTEGER16) | (1L << INTEGER32) | (1L << INTEGER64) | (1L << REAL16) | (1L << REAL32) | (1L << REAL64) | (1L << VOID) | (1L << IDENTIFIER))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 2:
			return expression_sempred((ExpressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expression_sempred(ExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 4);
		case 1:
			return precpred(_ctx, 3);
		case 2:
			return precpred(_ctx, 2);
		case 3:
			return precpred(_ctx, 1);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\64v\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t\13\3"+
		"\2\6\2\30\n\2\r\2\16\2\31\3\3\3\3\5\3\36\n\3\3\3\3\3\5\3\"\n\3\3\3\3\3"+
		"\5\3&\n\3\5\3(\n\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4\61\n\4\3\4\3\4\5\4"+
		"\65\n\4\5\4\67\n\4\3\4\3\4\3\4\5\4<\n\4\3\4\3\4\3\4\5\4A\n\4\3\4\3\4\3"+
		"\4\5\4F\n\4\3\4\3\4\3\4\5\4K\n\4\7\4M\n\4\f\4\16\4P\13\4\3\5\3\5\5\5T"+
		"\n\5\3\5\5\5W\n\5\3\6\3\6\5\6[\n\6\3\6\5\6^\n\6\3\6\5\6a\n\6\3\7\3\7\3"+
		"\7\3\b\3\b\3\t\3\t\5\tj\n\t\3\t\5\tm\n\t\3\t\5\tp\n\t\3\n\3\n\3\13\3\13"+
		"\3\13\2\3\6\f\2\4\6\b\n\f\16\20\22\24\2\t\4\2\')--\3\2*+\3\2()\3\2\37"+
		"$\4\2%&.\60\3\2\16\23\4\2\3\f\64\64\2\u0085\2\27\3\2\2\2\4\'\3\2\2\2\6"+
		"\66\3\2\2\2\bQ\3\2\2\2\nZ\3\2\2\2\fb\3\2\2\2\16e\3\2\2\2\20g\3\2\2\2\22"+
		"q\3\2\2\2\24s\3\2\2\2\26\30\5\4\3\2\27\26\3\2\2\2\30\31\3\2\2\2\31\27"+
		"\3\2\2\2\31\32\3\2\2\2\32\3\3\2\2\2\33\35\5\f\7\2\34\36\7\33\2\2\35\34"+
		"\3\2\2\2\35\36\3\2\2\2\36(\3\2\2\2\37!\5\n\6\2 \"\7\33\2\2! \3\2\2\2!"+
		"\"\3\2\2\2\"(\3\2\2\2#%\5\20\t\2$&\7\33\2\2%$\3\2\2\2%&\3\2\2\2&(\3\2"+
		"\2\2\'\33\3\2\2\2\'\37\3\2\2\2\'#\3\2\2\2(\5\3\2\2\2)\60\b\4\1\2*\61\7"+
		"\64\2\2+\61\5\22\n\2,-\7\25\2\2-.\5\6\4\2./\7\26\2\2/\61\3\2\2\2\60*\3"+
		"\2\2\2\60+\3\2\2\2\60,\3\2\2\2\61\67\3\2\2\2\62\64\t\2\2\2\63\65\5\6\4"+
		"\2\64\63\3\2\2\2\64\65\3\2\2\2\65\67\3\2\2\2\66)\3\2\2\2\66\62\3\2\2\2"+
		"\67N\3\2\2\289\f\6\2\29;\t\3\2\2:<\5\6\4\2;:\3\2\2\2;<\3\2\2\2<M\3\2\2"+
		"\2=>\f\5\2\2>@\t\4\2\2?A\5\6\4\2@?\3\2\2\2@A\3\2\2\2AM\3\2\2\2BC\f\4\2"+
		"\2CE\t\5\2\2DF\5\6\4\2ED\3\2\2\2EF\3\2\2\2FM\3\2\2\2GH\f\3\2\2HJ\t\6\2"+
		"\2IK\5\6\4\2JI\3\2\2\2JK\3\2\2\2KM\3\2\2\2L8\3\2\2\2L=\3\2\2\2LB\3\2\2"+
		"\2LG\3\2\2\2MP\3\2\2\2NL\3\2\2\2NO\3\2\2\2O\7\3\2\2\2PN\3\2\2\2QS\7\64"+
		"\2\2RT\7\36\2\2SR\3\2\2\2ST\3\2\2\2TV\3\2\2\2UW\5\6\4\2VU\3\2\2\2VW\3"+
		"\2\2\2W\t\3\2\2\2X[\5\f\7\2Y[\5\16\b\2ZX\3\2\2\2ZY\3\2\2\2[]\3\2\2\2\\"+
		"^\7\36\2\2]\\\3\2\2\2]^\3\2\2\2^`\3\2\2\2_a\5\6\4\2`_\3\2\2\2`a\3\2\2"+
		"\2a\13\3\2\2\2bc\5\24\13\2cd\7\64\2\2d\r\3\2\2\2ef\5\24\13\2f\17\3\2\2"+
		"\2gi\7\r\2\2hj\7\64\2\2ih\3\2\2\2ij\3\2\2\2jl\3\2\2\2km\7\36\2\2lk\3\2"+
		"\2\2lm\3\2\2\2mo\3\2\2\2np\5\24\13\2on\3\2\2\2op\3\2\2\2p\21\3\2\2\2q"+
		"r\t\7\2\2r\23\3\2\2\2st\t\b\2\2t\25\3\2\2\2\30\31\35!%\'\60\64\66;@EJ"+
		"LNSVZ]`ilo";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}