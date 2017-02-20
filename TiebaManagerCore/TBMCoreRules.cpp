﻿/*
Copyright (C) 2011-2017  xfgryujk
http://tieba.baidu.com/f?kw=%D2%BB%B8%F6%BC%AB%C6%E4%D2%FE%C3%D8%D6%BB%D3%D0xfgryujk%D6%AA%B5%C0%B5%C4%B5%D8%B7%BD

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "stdafx.h"
#include <TBMCoreRules.h>
using namespace tinyxml2;


// 规则 ///////////////////////////////////////////////////////////////////////////



// 条件 ///////////////////////////////////////////////////////////////////////////

void InitRules()
{
	CCondition::AddCondition(CKeywordCondition::GetInstance());
}


// 关键词条件

CString CKeywordCondition::GetDescription(const CConditionParam& _param)
{
	const auto& param = (CKeywordParam&)_param;
	static CString rangeDesc[] = {
		_T("主题标题"),
		_T("主题预览"),
		_T("帖子内容"),
		_T("楼中楼内容"),
		_T("作者名"),
		_T("所有内容")
	};
	
	CString res = rangeDesc[param.m_range];
	if (param.m_not)
		res += _T("不");
	res += param.m_include ? _T("含有") : _T("匹配");
	res += param.m_keyword.isRegex ? _T("正则表达式\"") : _T("\"");
	res += param.m_keyword.text;
	res += _T("\"");
	return res;
}


CConditionParam* CKeywordCondition::ReadParam(const tinyxml2::XMLElement* optionNode)
{
	CKeywordParam* param = new CKeywordParam();

	param->m_conditionName = m_name;
	COption<int> range("Range");
	COption<BOOL> not("Not");
	COption<BOOL> include("Include");
	COption<RegexText> keyword("Keyword");
	range.Read(*optionNode);
	not.Read(*optionNode);
	include.Read(*optionNode);
	keyword.Read(*optionNode);

	param->m_range = (0 <= range && range <= KeywordRange::ALL_CONTENT) ? KeywordRange(*range) : KeywordRange::ALL_CONTENT;
	param->m_not = not;
	param->m_include = include;
	param->m_keyword = keyword;

	return param;
}

void WriteParam(const CConditionParam& _param, tinyxml2::XMLElement* optionNode)
{
	const auto& param = (CKeywordParam&)_param;

	COption<int> range("Range");
	*range = param.m_range;
	range.Write(*optionNode);
	COption<BOOL> not("Not");
	*not = param.m_not;
	not.Write(*optionNode);
	COption<BOOL> include("Include");
	*include = param.m_include;
	include.Write(*optionNode);
	COption<RegexText> keyword("Keyword");
	*keyword = param.m_keyword;
	keyword.Write(*optionNode);
}
