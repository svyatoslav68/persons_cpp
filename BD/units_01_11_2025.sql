--
-- PostgreSQL database dump
--

-- Dumped from database version 17.5 (Debian 17.5-1)
-- Dumped by pg_dump version 17.5 (Debian 17.5-1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: t_family_members; Type: TYPE; Schema: public; Owner: slava
--

CREATE TYPE public.t_family_members AS ENUM (
    'отец',
    'мать',
    'жена',
    'муж',
    'сын',
    'дочь',
    'сестра',
    'брат'
);


ALTER TYPE public.t_family_members OWNER TO slava;

--
-- Name: t_visual_unit; Type: TYPE; Schema: public; Owner: slava
--

CREATE TYPE public.t_visual_unit AS ENUM (
    'before',
    'after',
    'none'
);


ALTER TYPE public.t_visual_unit OWNER TO slava;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: members; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.members (
    id_member integer NOT NULL,
    type_member public.t_family_members NOT NULL,
    family text NOT NULL,
    past_family text[],
    birthday date DEFAULT '1900-01-01'::date NOT NULL,
    cod_person integer NOT NULL,
    name text NOT NULL,
    parent text NOT NULL
);


ALTER TABLE public.members OWNER TO slava;

--
-- Name: members_id_member_seq; Type: SEQUENCE; Schema: public; Owner: slava
--

CREATE SEQUENCE public.members_id_member_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.members_id_member_seq OWNER TO slava;

--
-- Name: members_id_member_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: slava
--

ALTER SEQUENCE public.members_id_member_seq OWNED BY public.members.id_member;


--
-- Name: persons; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.persons (
    idperson integer NOT NULL,
    family character varying,
    name character varying,
    parent character varying,
    current_unit integer,
    codes_prever_units integer[],
    birthday date DEFAULT '1970-01-01'::date NOT NULL
);


ALTER TABLE public.persons OWNER TO slava;

--
-- Name: persons_idperson_seq; Type: SEQUENCE; Schema: public; Owner: slava
--

CREATE SEQUENCE public.persons_idperson_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.persons_idperson_seq OWNER TO slava;

--
-- Name: persons_idperson_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: slava
--

ALTER SEQUENCE public.persons_idperson_seq OWNED BY public.persons.idperson;


--
-- Name: ten; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.ten (
    id integer NOT NULL,
    value integer NOT NULL
);


ALTER TABLE public.ten OWNER TO slava;

--
-- Name: units; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.units (
    idunit integer NOT NULL,
    number integer DEFAULT '-1'::integer NOT NULL,
    name character varying NOT NULL,
    parent integer DEFAULT '-1'::integer NOT NULL,
    type character varying NOT NULL,
    visualization public.t_visual_unit NOT NULL
);


ALTER TABLE public.units OWNER TO slava;

--
-- Name: units_idunit_seq; Type: SEQUENCE; Schema: public; Owner: slava
--

CREATE SEQUENCE public.units_idunit_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.units_idunit_seq OWNER TO slava;

--
-- Name: units_idunit_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: slava
--

ALTER SEQUENCE public.units_idunit_seq OWNED BY public.units.idunit;


--
-- Name: members id_member; Type: DEFAULT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.members ALTER COLUMN id_member SET DEFAULT nextval('public.members_id_member_seq'::regclass);


--
-- Name: persons idperson; Type: DEFAULT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.persons ALTER COLUMN idperson SET DEFAULT nextval('public.persons_idperson_seq'::regclass);


--
-- Name: units idunit; Type: DEFAULT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.units ALTER COLUMN idunit SET DEFAULT nextval('public.units_idunit_seq'::regclass);


--
-- Data for Name: members; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.members (id_member, type_member, family, past_family, birthday, cod_person, name, parent) FROM stdin;
1	отец	Воронин	\N	1941-01-17	1	Петр	Васильевич
2	брат	Воронин	\N	1964-01-24	1	Евгений	Петрович
3	сестра	Антипенкова	{Воронина}	1974-08-07	1	Анна	Петровна
\.


--
-- Data for Name: persons; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.persons (idperson, family, name, parent, current_unit, codes_prever_units, birthday) FROM stdin;
5	Кузнецов	Андрей	Викторович	31	\N	1970-01-01
8	Орлов	Евгений	Владимирович	20	\N	1970-01-01
11	Пилюгин	Олег	Игоревич	26	\N	1970-01-01
1	Воронин	Святослав	Петрович	31	\N	1968-05-09
2	Гришенков	Владимир	Дмитриевич	31	\N	1956-11-07
7	Андреев	Александр	Юрьевич	20	\N	1978-04-09
9	Лабунец	Артем	Владимирович	26	\N	1979-11-02
10	Колосов	Сергей	Александрович	26	\N	1983-01-05
6	Никольский	Павел	Геннадьевич	31	\N	1996-07-08
3	Батенков	Кирилл	Александрович	31	\N	1981-06-15
4	Козленко	Андрей	Владимирович	31	\N	1970-01-01
23	Журавлев	Дмитрий	Витальевич	26	\N	1970-01-01
\.


--
-- Data for Name: ten; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.ten (id, value) FROM stdin;
1	1
2	2
3	3
4	4
5	5
6	6
7	7
8	8
9	9
0	0
\.


--
-- Data for Name: units; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.units (idunit, number, name, parent, type, visualization) FROM stdin;
0	-1	ФСО	-1	ведомство	none
1	-1	СССИ	0	служба	none
2	-1	УНТО	1	управление	none
3	-1	УЭССС	1	управление	none
4	-1	УПС	1	управление	none
5	-1	УПрС	1	управление	none
12	-1	секретариат	2		none
14	-1	секретариат	3		none
6	1		2	отдел	after
7	2		2	отдел	after
8	3		2	отдел	after
9	4		2	отдел	after
10	5		2	отдел	after
15	1		3	отдел	after
16	2		3	отдел	after
17	3		3	отдел	after
18	4		3	отдел	after
19	5		3	отдел	after
20	6		3	отдел	after
21	7		3	отдел	after
22	8		3	отдел	after
23	9		3	отдел	after
11	-1	кадров	2	группа	before
13	-1	кадров	3	отделение	before
28	-1	мобилизационное	0	управление	after
29	1		7	отделение	after
30	2		7	отделение	after
31	6		2	отдел	after
24	1		20	отделение	after
25	2		20	отделение	after
26	4		20	отделение	after
27	3		20	группа	after
33	1		25	группа	after
34	2		25	группа	after
35	3		25	группа	after
36	4		25	группа	after
37	1		16	отделение	after
38	2		16	отделение	after
39	3		16	отделение	after
40	4		16	отделение	after
41	5		16	отделение	after
42	1		41	группа	after
43	2		41	группа	after
44	3		41	группа	after
45	1		28	отдел	after
46	2		28	отдел	after
47	1		19	отделение	after
32	7	организации метрологического обеспечения ОГО	2	группа	before
\.


--
-- Name: members_id_member_seq; Type: SEQUENCE SET; Schema: public; Owner: slava
--

SELECT pg_catalog.setval('public.members_id_member_seq', 3, true);


--
-- Name: persons_idperson_seq; Type: SEQUENCE SET; Schema: public; Owner: slava
--

SELECT pg_catalog.setval('public.persons_idperson_seq', 23, true);


--
-- Name: units_idunit_seq; Type: SEQUENCE SET; Schema: public; Owner: slava
--

SELECT pg_catalog.setval('public.units_idunit_seq', 47, true);


--
-- Name: persons persons_idperson_key; Type: CONSTRAINT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.persons
    ADD CONSTRAINT persons_idperson_key UNIQUE (idperson);


--
-- Name: ten ten_pkey; Type: CONSTRAINT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.ten
    ADD CONSTRAINT ten_pkey PRIMARY KEY (id);


--
-- Name: units units_idunit_key; Type: CONSTRAINT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.units
    ADD CONSTRAINT units_idunit_key UNIQUE (idunit);


--
-- Name: persons persons_cod_unit_fkey; Type: FK CONSTRAINT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.persons
    ADD CONSTRAINT persons_cod_unit_fkey FOREIGN KEY (current_unit) REFERENCES public.units(idunit);


--
-- PostgreSQL database dump complete
--

